#include "workstation_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "udp_transceiver.h"
#include "board_packet.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class WorkstationTransceiverNode::Impl
{
public:
    AbstractTransceiver* transceiver;
    Subscriber sub;
    Publisher pub;
};

WorkstationTransceiverNode::WorkstationTransceiverNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    Config::begin("Transceiver");
    d->transceiver = new UdpTransceiver(
                         QHostAddress(Config::setting("udp_workstation_address").toString()),
                         Config::setting("udp_workstation_port").toInt(),
                         QHostAddress(Config::setting("udp_board_address").toString()),
                         Config::setting("udp_board_port").toInt(), this);

    d->pub.bind("ipc://transceiver");
    d->pub.setTopic("tr_");
    Config::end();
}

WorkstationTransceiverNode::~WorkstationTransceiverNode()
{
    delete d->transceiver;
    delete d;
}

void WorkstationTransceiverNode::init()
{
//     d->sub.connectTo("ipc://???"); TODO: command line

//     d->sub.subscribe("");
//     connect(&d->sub, &Subscriber::received, this,
//             &WorkstationTransceiverNode::onReceived);

    connect(d->transceiver, &AbstractTransceiver::received,
            this, &WorkstationTransceiverNode::onPacketReceived);
}

void WorkstationTransceiverNode::exec()
{
    // TODO: send command packet
}

void WorkstationTransceiverNode::onPacketReceived(const QByteArray& packetData)
{
    QDataStream stream(packetData);
    BoardPacket packet;
    stream >> packet;

    if (!packet.validateCrc())
    {
        d->pub.publish("status", QByteArray::number(false));
        return;
    }
    d->pub.publish("status", QByteArray::number(true));

    d->pub.publish("alt_status", QByteArray::number(packet.data.altimeterStatus));


//    //  TODO: topics string constants to header
//    if (topic == "alt_status") stream >> d->packet.data.altimeterStatus;
//    else if (topic == "alt_altitude") stream >> d->packet.data.altitude;
//    else if (topic == "alt_temperature") stream >> d->packet.data.temperature;
//    else if (topic == "ins_status") stream >> d->packet.data.insStatus;
//    else if (topic == "ins_pitch") stream >> d->packet.data.pitch;
//    else if (topic == "ins_roll") stream >> d->packet.data.roll;
//    else if (topic == "ins_yaw") stream >> d->packet.data.yaw;
//    else if (topic == "sns_status") stream >> d->packet.data.snsStatus;
//    else if (topic == "sns_latitude") stream >> d->packet.data.latitude;
//    else if (topic == "sns_longitude") stream >> d->packet.data.longitude;
//    else if (topic == "sns_velocity") stream >> d->packet.data.velocity;
//    else if (topic == "sns_climb") stream >> d->packet.data.climb;
}
