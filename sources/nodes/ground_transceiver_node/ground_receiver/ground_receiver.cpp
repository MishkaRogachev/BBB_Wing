#include "ground_receiver.h"

// Internal
#include "core.h"

#include "crc_packet.h"
#include "reverse_packet.h"

using namespace domain;

GroundReceiver::GroundReceiver(QObject* parent):
    QObject(parent)
{}

void GroundReceiver::onLinkReceived(const QByteArray& data)
{
    auto crcPacket = CrcPacket::fromByteArray(data);
    if (!crcPacket.validateCrc()) return;

    if (crcPacket.topic == topics::directPacket)
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
