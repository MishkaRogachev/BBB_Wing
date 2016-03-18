#include "workstation_transmitter_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"

#include "ground_packet.h"

using namespace domain;

class WorkstationTransmitterNode::Impl
{
public:
    GroundPacket packet;
};

WorkstationTransmitterNode::WorkstationTransmitterNode(float frequency,
                                                       QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

WorkstationTransmitterNode::~WorkstationTransmitterNode()
{
    delete d;
}

void WorkstationTransmitterNode::exec()
{
    d->packet.calcCrc();

    QByteArray packetData;
    QDataStream stream(&packetData, QIODevice::WriteOnly);
    stream << d->packet;

    emit transmit(packetData);
}

void WorkstationTransmitterNode::onSubReceived(
        const QString& topic, const QByteArray& msg)
{
    // TODO: collect ground packet
    d->packet.data.isManual = true;
    d->packet.data.manual.setPitch = 0.0;
    d->packet.data.manual.setRoll = 0.0;
    d->packet.data.manual.setThrottle = 0;
}
