#ifndef BOARD_PACKET_H
#define BOARD_PACKET_H

// Internal
#include "sns_packet.h"

namespace domain
{
    class BoardDataPacket: public Packet
    {
    public:
        float altimeterAltitude;

        float pitch;
        float roll;
        float yaw;

        float temperature;

        SnsPacket sns;

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
