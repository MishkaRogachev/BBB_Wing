#include "board_receiver.h"

// Internal
#include "crc_packet.h"

using namespace domain;

BoardReceiver::BoardReceiver(QObject* parent):
    QObject(parent)
{}

void BoardReceiver::onLinkReceived(const QByteArray& data)
{
    auto packet = CrcPacket::fromByteArray(data);
    if (!packet.validateCrc()) return;

    // TODO: disassemble direct packet
    emit publish(packet.topic, packet.data);
}
