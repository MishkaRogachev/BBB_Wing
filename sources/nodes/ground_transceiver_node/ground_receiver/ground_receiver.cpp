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
        auto reverse = ReversePacket::fromByteArray(crcPacket.data);

        if (reverse.altAvalible)
            emit publish(topics::altPacket, reverse.alt.toByteArray());
        if (reverse.insAvalible)
            emit publish(topics::insPacket, reverse.ins.toByteArray());
        if (reverse.snsAvalible)
            emit publish(topics::snsPacket, reverse.sns.toByteArray());
        if (reverse.controlAvalible)
            emit publish(topics::controlPacket, reverse.control.toByteArray());

        emit publish(topics::reverseStatusPacket, reverse.status().toByteArray());
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
