#ifndef BOARD_PACKET_H
#define BOARD_PACKET_H

#include "packets.h"

namespace domain
{
    class BoardDataPacket: public Packet
    {
    public:
        float latitude;
        float longitude;
        float altimeterAltitude;

        float velocity;
        float climb;

        float pitch;
        float roll;
        float yaw;

        float temperature;

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
