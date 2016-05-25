#ifndef BOARD_TRANSMITTER_H
#define BOARD_TRANSMITTER_H

// Qt
#include <QObject>

namespace domain
{
    class AbstractLink;

    class BoardTransmitter: public QObject
    {
        Q_OBJECT

    public:
        explicit BoardTransmitter(QObject* parent = nullptr);
        ~BoardTransmitter() override;

        void transmit(AbstractLink* link);

    public slots:
        void setAltData(const QByteArray& data);
        void setInsData(const QByteArray& data);
        void setSnsData(const QByteArray& data);
        void setControlData(const QByteArray& data);

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_TRANSMITTER_H
