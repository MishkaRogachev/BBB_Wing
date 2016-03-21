#ifndef ABSTRACT_EXCHANGER_H
#define ABSTRACT_EXCHANGER_H

#include <QObject>

namespace domain
{
    class AbstractExchanger: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractExchanger(QObject* parent = nullptr);
        ~AbstractExchanger() override;

        virtual bool isAvailable() const = 0;

    public slots:
        virtual bool start() = 0;
        virtual void transmit(const QByteArray& packet) = 0;

    signals:
        void received(const QByteArray& packet);
    };
}

#endif // ABSTRACT_EXCHANGER_H
