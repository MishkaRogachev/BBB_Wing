#include "workstation_receiver_node.h"

// Internal
#include "topics.h"
#include "publisher.h"
#include "board_packet.h"
#include "connection_status_packet.h"

using namespace domain;

WorkstationReceiverNode::WorkstationReceiverNode(
        float frequency, Publisher* pub, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    m_pub(pub),
    m_badCount(0),
    m_goodCount(0)
{}

void WorkstationReceiverNode::exec()
{
    ConnectionStatusPacket packet;

    packet.wireLine = false;
    packet.airLine = false; // TODO: Transceivers to gateway

    packet.packetsPerSecond = (m_goodCount * this->frequency());
    if (m_goodCount + m_badCount)
    {
        packet.badPackets = 100 * m_badCount / (m_goodCount + m_badCount);
    }
    else
    {
        packet.badPackets = 0;
        emit timeout();
    }

    m_badCount = 0;
    m_goodCount = 0;

    m_pub->publish(topics::connectionStatusPacket, packet.toByteArray());
}

void WorkstationReceiverNode::processPacket(const QByteArray& packetData)
{
    QDataStream stream(packetData);
    BoardPacket packet;
    stream >> packet;

    if (!packet.validateCrc())
    {
        m_badCount++;
        return;
    }
    m_goodCount++;

    m_pub->publish(topics::altStatus, QByteArray::number(packet.data.altimeterStatus));
    m_pub->publish(topics::altPacket, packet.data.alt.toByteArray());
    m_pub->publish(topics::insStatus, QByteArray::number(packet.data.insStatus));
    m_pub->publish(topics::insPacket, packet.data.ins.toByteArray());
    m_pub->publish(topics::snsStatus, QByteArray::number(packet.data.snsStatus));
    m_pub->publish(topics::snsPacket, packet.data.sns.toByteArray());
}
