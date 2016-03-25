#ifndef BOARD_PACKET_H
#define BOARD_PACKET_H

// Internal
#include "alt_packet.h"
#include "sns_packet.h"
#include "ins_packet.h"

namespace domain
{
    // Remove Board packet with covered local packets
    class BoardDataPacket: public Packet
    {
    public:
        AltPacket alt;
        SnsPacket sns;
        InsPacket ins;

        bool altimeterStatus;
        bool insStatus;
        bool snsStatus;

        quint16 crc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;
    };

    using BoardPacket = DataPacket<BoardDataPacket>;
}

#endif // BOARD_PACKET_H
