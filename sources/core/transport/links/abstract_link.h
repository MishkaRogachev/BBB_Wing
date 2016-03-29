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

        virtual bool isAvailable() const = 0;

    public slots:
        virtual bool start() = 0;
        virtual void transmit(const QByteArray& packet) = 0;

    signals:
        void received(const QByteArray& packet);
    };
}

#endif // ABSTRACT_LINK_H
