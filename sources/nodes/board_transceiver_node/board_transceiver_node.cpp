#include "board_transceiver_node.h"

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

class BoardTransceiverNode::Impl
{
public:
    QList<AbstractTransceiver*> transceivers;
    BoardPacket packet;
    Subscriber sub;
    Publisher pub;
};

BoardTransceiverNode::BoardTransceiverNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    Config::begin("Transceiver");
    d->transceivers.append(new UdpTransceiver(
        QHostAddress(Config::setting("udp_board_address").toString()),
        Config::setting("udp_board_port").toInt(),
        QHostAddress(Config::setting("udp_workstation_address").toString()),
        Config::setting("udp_workstation_port").toInt(), this));

    d->transceivers.append(new SerialPortTransceiver(
        Config::setting("serial_port_board").toString(), this));

    d->pub.bind("ipc://transceiver");
    Config::end();
}

BoardTransceiverNode::~BoardTransceiverNode()
{
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

    for (AbstractTransceiver* transceiver: d->transceivers)
        transceiver->transmit(packetData);
}

void BoardTransceiverNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::altimeterStatus) d->packet.data.altimeterStatus = msg.toInt();
    else if (topic == topics::altimeterAltitude) d->packet.data.altimeterAltitude = msg.toFloat();
    else if (topic == topics::altimeterTemperature) d->packet.data.temperature = msg.toFloat();
    else if (topic == topics::insStatus) d->packet.data.insStatus = msg.toInt();
    else if (topic == topics::insPitch) d->packet.data.pitch = msg.toFloat();
    else if (topic == topics::insRoll) d->packet.data.roll = msg.toFloat();
    else if (topic == topics::insYaw) d->packet.data.yaw = msg.toFloat();
    else if (topic == topics::snsStatus) d->packet.data.snsStatus = msg.toInt();
    else if (topic == topics::snsLatitude) d->packet.data.latitude = msg.toFloat();
    else if (topic == topics::snsLongitude) d->packet.data.longitude = msg.toFloat();
    else if (topic == topics::snsVelocity) d->packet.data.velocity = msg.toFloat();
    else if (topic == topics::snsClimb) d->packet.data.climb = msg.toFloat();
}
