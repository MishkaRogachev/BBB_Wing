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

    //  TODO: topics string constants to header
    //  TODO: topics must be grouped and minimized(local packets)
    d->pub.publish("alt_status", QByteArray::number(packet.data.altimeterStatus));
    d->pub.publish("altitude", QByteArray::number(packet.data.altitude));
    d->pub.publish("temperature", QByteArray::number(packet.data.temperature));
    d->pub.publish("ins_status", QByteArray::number(packet.data.insStatus));
    d->pub.publish("pitch", QByteArray::number(packet.data.pitch));
    d->pub.publish("roll", QByteArray::number(packet.data.roll));
    d->pub.publish("yaw", QByteArray::number(packet.data.yaw));
    d->pub.publish("sns_status", QByteArray::number(packet.data.snsStatus));
    d->pub.publish("latitude", QByteArray::number(packet.data.latitude));
    d->pub.publish("longitude", QByteArray::number(packet.data.longitude));
    d->pub.publish("velocity", QByteArray::number(packet.data.velocity));
    d->pub.publish("climb", QByteArray::number(packet.data.climb));
}
