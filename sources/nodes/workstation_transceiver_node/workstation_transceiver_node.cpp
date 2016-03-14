#include "workstation_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "config.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_transceiver.h"
#include "serial_port_transceiver.h"

#include "board_packet.h"

using namespace domain;

class WorkstationTransceiverNode::Impl
{
public:
    QList<AbstractTransceiver*> transceivers;
    Subscriber sub;
    Publisher pub;
};

WorkstationTransceiverNode::WorkstationTransceiverNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    Config::begin("Transceiver");

    d->transceivers.append(new UdpTransceiver(
        QHostAddress(Config::setting("udp_workstation_address").toString()),
        Config::setting("udp_workstation_port").toInt(),
        QHostAddress(Config::setting("udp_board_address").toString()),
        Config::setting("udp_board_port").toInt(), this));

    d->transceivers.append(new SerialPortTransceiver(
        Config::setting("serial_port_workstation").toString(),
                               sizeof(BoardPacket), this)); // TODO: different board packets

    d->pub.bind("ipc://transceiver");
    Config::end();
}

WorkstationTransceiverNode::~WorkstationTransceiverNode()
{
    delete d;
}

void WorkstationTransceiverNode::init()
{
//     d->sub.connectTo("ipc://???"); TODO: command line

//     d->sub.subscribe("");
//     connect(&d->sub, &Subscriber::received, this,
//             &WorkstationTransceiverNode::onReceived);

    for (AbstractTransceiver* transceiver: d->transceivers)
        connect(transceiver, &AbstractTransceiver::received,
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
        d->pub.publish(topics::transceiverStatus, QByteArray::number(false));
        return;
    }

    d->pub.publish(topics::transceiverStatus, QByteArray::number(true));

    //  TODO: topics must be grouped and minimized(local packets)
    d->pub.publish(topics::altimeterStatus, QByteArray::number(packet.data.altimeterStatus));
    d->pub.publish(topics::altimeterAltitude, QByteArray::number(packet.data.altimeterAltitude));
    d->pub.publish(topics::altimeterTemperature, QByteArray::number(packet.data.temperature));
    d->pub.publish(topics::insStatus, QByteArray::number(packet.data.insStatus));
    d->pub.publish(topics::insPitch, QByteArray::number(packet.data.pitch));
    d->pub.publish(topics::insRoll, QByteArray::number(packet.data.roll));
    d->pub.publish(topics::insYaw, QByteArray::number(packet.data.yaw));
    d->pub.publish(topics::snsStatus, QByteArray::number(packet.data.snsStatus));
    d->pub.publish(topics::snsLatitude, QByteArray::number(packet.data.latitude));
    d->pub.publish(topics::snsLongitude, QByteArray::number(packet.data.longitude));
    d->pub.publish(topics::snsVelocity, QByteArray::number(packet.data.velocity));
    d->pub.publish(topics::snsClimb, QByteArray::number(packet.data.climb));
}
