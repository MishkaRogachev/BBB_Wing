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
     connect(&d->sub, &Subscriber::received, this,
             &BoardTransceiverNode::onSubReceived);
}

void BoardTransceiverNode::exec()
{
    d->packet.calcCrc();

    QByteArray packetData;
    QDataStream stream(&packetData, QIODevice::WriteOnly);
    stream << d->packet;

    d->transceiver->transmit(packetData);
}

void BoardTransceiverNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    //  TODO: topics string constants to header
    if (topic == "alt_status") d->packet.data.altimeterStatus = msg.toInt();
    else if (topic == "alt_altitude") d->packet.data.altitude = msg.toFloat();
    else if (topic == "alt_temperature") d->packet.data.temperature = msg.toFloat();
    else if (topic == "ins_status") d->packet.data.insStatus = msg.toInt();
    else if (topic == "ins_pitch") d->packet.data.pitch = msg.toFloat();
    else if (topic == "ins_roll") d->packet.data.roll = msg.toFloat();
    else if (topic == "ins_yaw") d->packet.data.yaw = msg.toFloat();
    else if (topic == "sns_status") d->packet.data.snsStatus = msg.toInt();
    else if (topic == "sns_latitude") d->packet.data.latitude = msg.toFloat();
    else if (topic == "sns_longitude") d->packet.data.longitude = msg.toFloat();
    else if (topic == "sns_velocity") d->packet.data.velocity = msg.toFloat();
    else if (topic == "sns_climb") d->packet.data.climb = msg.toFloat();
}
