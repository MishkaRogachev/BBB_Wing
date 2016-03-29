#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

#include <QObject>

namespace domain
{
    class AbstractLink: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractLink(QObject* parent = nullptr);
        ~AbstractLink() override;

        virtual bool isConnected() const = 0;

    public slots:
        virtual bool connect() = 0;
        virtual void disconnect() = 0;
        virtual void transmit(const QByteArray& packet) = 0;

        void tryTransmit(const QByteArray& packet);

    signals:
        void received(const QByteArray& packet);

    private:
        Q_DISABLE_COPY(AbstractLink)
    };
}

#endif // ABSTRACT_LINK_H
