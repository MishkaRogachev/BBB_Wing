#ifndef REVERSE_PACKET_H
#define REVERSE_PACKET_H

#include "reverse_status_packet.h"
#include "alt_packet.h"
#include "ins_packet.h"
#include "sns_packet.h"
#include "control_packet.h"

namespace domain
{
    class ReversePacket: public ReverseStatusPacket
    {
    public:
        AltPacket alt;
        InsPacket ins;
        SnsPacket sns;
        ControlPacket control;

        ReverseStatusPacket status() const;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ReversePacket fromByteArray(const QByteArray& data);
    };
}

#endif // REVERSE_PACKET_H
