#ifndef BOARD_PACKET_H
#define BOARD_PACKET_H

#include "base_packet.h"

namespace domain
{
    struct BoardPacket: public BasePacket
    {
        float latitude;
        float longitude;
        float altitude;

        float velocity;
        float climb;

        float pitch;
        float roll;
        float yaw;

        float temperature;

        bool altimeterStatus;
        bool insStatus;
        bool snsStatus;

//        QDataStream& operator >>(QDataStream& stream) override;
//        QDataStream& operator <<(QDataStream& stream) override;
    };
}

#endif // BOARD_PACKET_H
