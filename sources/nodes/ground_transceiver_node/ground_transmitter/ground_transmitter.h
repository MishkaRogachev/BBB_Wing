#ifndef GROUND_TRANSMITTER_H
#define GROUND_TRANSMITTER_H

#include <QObject>

// Internal
#include "direct_packet.h"

namespace domain
{
    class AbstractLink;

    class GroundTransmitter: public QObject
    {
        Q_OBJECT

    public:
        explicit GroundTransmitter(QObject* parent = nullptr);

        void transmit(AbstractLink* link);

    public slots:
        void setManualData(const QByteArray& data);
        void setAutomaticData(const QByteArray& data);

    private:
        DirectPacket m_packet;
    };
}

#endif // GROUND_TRANSMITTER_H
