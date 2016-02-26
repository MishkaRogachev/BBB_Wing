#include "board_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "udp_transceiver.h"
#include "board_packet.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class BoardTransceiverNode::Impl
{
public:
    AbstractTransceiver* transceiver;
    BoardPacket packet;
    Subscriber sub;
    Publisher pub;
};

BoardTransceiverNode::BoardTransceiverNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    Config::begin("Transceiver");
    d->transceiver = new UdpTransceiver(
                         QHostAddress(Config::setting("udp_board_address").toString()),
                         Config::setting("udp_board_port").toInt(),
                         QHostAddress(Config::setting("udp_workstation_address").toString()),
                         Config::setting("udp_workstation_port").toInt(), this);

    d->pub.bind("ipc://transceiver");
    d->pub.setTopic("tr_");
    Config::end();
}

BoardTransceiverNode::~BoardTransceiverNode()
{
    delete d->transceiver;
    delete d;
}

void BoardTransceiverNode::init()
{
     d->sub.connectTo("ipc://altimeter");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this, &BoardTransceiverNode::onReceived);
}

void BoardTransceiverNode::exec()
{
    d->packet.calcCrc();

    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream << d->packet;

    d->transceiver->transmit(packet);
}

void BoardTransceiverNode::onReceived(const QString& topic, const QByteArray& msg)
{
    QDataStream stream(msg);

    //  TODO: topics string constants to header
    if (topic == "alt_status") stream >> d->packet.data.altimeterStatus;
    else if (topic == "alt_altitude") stream >> d->packet.data.altitude;
    else if (topic == "alt_temperature") stream >> d->packet.data.temperature;
    else if (topic == "ins_status") stream >> d->packet.data.insStatus;
    else if (topic == "ins_pitch") stream >> d->packet.data.pitch;
    else if (topic == "ins_roll") stream >> d->packet.data.roll;
    else if (topic == "ins_yaw") stream >> d->packet.data.yaw;
    else if (topic == "sns_status") stream >> d->packet.data.snsStatus;
    else if (topic == "sns_latitude") stream >> d->packet.data.latitude;
    else if (topic == "sns_longitude") stream >> d->packet.data.longitude;
    else if (topic == "sns_velocity") stream >> d->packet.data.velocity;
    else if (topic == "sns_climb") stream >> d->packet.data.climb;
}
