#include "board_transmitter_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"

#include "board_packet.h"

using namespace domain;

class BoardTransmitterNode::Impl
{
public:
    BoardPacket packet;
};

BoardTransmitterNode::BoardTransmitterNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

BoardTransmitterNode::~BoardTransmitterNode()
{
    delete d;
}

void BoardTransmitterNode::exec()
{
    d->packet.calcCrc();

    QByteArray packetData;
    QDataStream stream(&packetData, QIODevice::WriteOnly);
    stream << d->packet;

    emit transmit(packetData);
}

void BoardTransmitterNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::altimeterStatus) d->packet.data.altimeterStatus = msg.toInt();
    else if (topic == topics::altimeterAltitude) d->packet.data.altimeterAltitude = msg.toFloat();
    else if (topic == topics::altimeterTemperature) d->packet.data.temperature = msg.toFloat();
    else if (topic == topics::insStatus) d->packet.data.insStatus = msg.toInt();
    else if (topic == topics::insPacket) d->packet.data.ins = InsPacket::fromByteArray(msg);
    else if (topic == topics::snsStatus) d->packet.data.snsStatus = msg.toInt();
    else if (topic == topics::snsPacket) d->packet.data.sns = SnsPacket::fromByteArray(msg);

}
