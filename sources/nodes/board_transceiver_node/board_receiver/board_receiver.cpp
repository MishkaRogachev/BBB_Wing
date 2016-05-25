#include "board_receiver.h"

// Internal
#include "core.h"

#include "crc_packet.h"
#include "direct_packet.h"

using namespace domain;

BoardReceiver::BoardReceiver(QObject* parent):
    QObject(parent)
{}

void BoardReceiver::onLinkReceived(const QByteArray& data)
{
    auto crcPacket = CrcPacket::fromByteArray(data);
    if (!crcPacket.validateCrc()) return;

    if (crcPacket.topic == topics::directPacket)
    {
        auto directPacket = DirectPacket::fromByteArray(crcPacket.data);

        if (directPacket.isManual)
            emit publish(topics::controlPacket, directPacket.manual.toByteArray());
        else
            emit publish(topics::automaticPacket, directPacket.automatic.toByteArray());
    }
}
