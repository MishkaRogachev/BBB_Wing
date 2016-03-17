#include "workstation_transmitter_node.h"

using namespace domain;

WorkstationTransmitterNode::WorkstationTransmitterNode(float frequency,
                                                       QObject* parent):
    AbstractNodeFrequency(frequency, parent)
{}

void WorkstationTransmitterNode::exec()
{
    // TODO: emit command packet data
}

void WorkstationTransmitterNode::onSubReceived(
        const QString& topic, const QByteArray& msg)
{
    // TODO: collect command packet
}
