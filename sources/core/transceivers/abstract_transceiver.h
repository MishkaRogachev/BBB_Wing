#ifndef ABSTRACT_TRANSCEIVER_H
#define ABSTRACT_TRANSCEIVER_H

#include <QObject>

namespace domain
{
    class AbstractTransceiver: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractTransceiver(QObject* parent = nullptr);
        ~AbstractTransceiver() override;

    public slots:
        virtual void transmit(const QByteArray& packet) = 0;

    signals:
        void received(const QByteArray& packet);
    };
}

#endif // ABSTRACT_TRANSCEIVER_H
