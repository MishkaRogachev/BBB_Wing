#ifndef REVERSE_PACKET_H
#define REVERSE_PACKET_H

#include "alt_packet.h"
#include "ins_packet.h"
#include "sns_packet.h"
#include "control_packet.h"

namespace domain
{
    class ReversePacket: public Packet
    {
    public:
        bool altAvalible;
        AltPacket alt;

        bool insAvalible;
        InsPacket ins;

        bool snsAvalible;
        SnsPacket sns;

        bool controlAvalible;
        ControlPacket control;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ReversePacket fromByteArray(const QByteArray& data);
    };
}

#endif // REVERSE_PACKET_H
