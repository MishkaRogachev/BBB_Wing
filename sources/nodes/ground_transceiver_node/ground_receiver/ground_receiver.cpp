#include "ground_receiver.h"

// Internal
#include "core.h"

#include "crc_packet.h"
#include "reverse_packet.h"

// Qt
#include <QDebug>

using namespace domain;

GroundReceiver::GroundReceiver(QObject* parent):
    QObject(parent)
{}

void GroundReceiver::onLinkReceived(const QByteArray& data)
{
    m_count++;

    auto crcPacket = CrcPacket::fromByteArray(data);
    if (!crcPacket.validateCrc())
    {
        m_packetsLost++;
        return;
    }

    if (crcPacket.topic == topics::reversePacket)
    {
        auto reversePacket = ReversePacket::fromByteArray(crcPacket.data);

        if (reversePacket.altAvalible)
            emit publish(topics::altPacket, reversePacket.alt.toByteArray());
        if (reversePacket.insAvalible)
            emit publish(topics::insPacket, reversePacket.ins.toByteArray());
        if (reversePacket.snsAvalible)
            emit publish(topics::snsPacket, reversePacket.sns.toByteArray());
        if (reversePacket.controlAvalible)
            emit publish(topics::controlPacket, reversePacket.control.toByteArray());
    }
}

void GroundReceiver::reset()
{
    m_packetsLost = 0;
    m_count = 0;
}

int GroundReceiver::packetsLost() const
{
    return m_packetsLost;
}

int GroundReceiver::count() const
{
    return m_count;
}
