#ifndef BOARD_PACKET_H
#define BOARD_PACKET_H

#include "packets.h"

namespace domain
{
    class BoardPacket: public Packet { // TODO: template CrcPacket<BoardDataPacket>
    public:
        quint16 crc;

        bool validateCrc();
        void calcCrc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        class BoardDataPacket: public DataPacket
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

            QDataStream& operator >>(QDataStream& stream) const override;
            QDataStream& operator <<(QDataStream& stream) override;
        } data;
    };
}

#endif // BOARD_PACKET_H
