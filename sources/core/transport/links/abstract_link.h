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
        virtual bool connectLink() = 0;
        virtual void disconnectLink() = 0;
        virtual void send(const QByteArray& packet) = 0;

    signals:
        void received(const QByteArray& packet);

    private:
        Q_DISABLE_COPY(AbstractLink)
    };
}

#endif // ABSTRACT_LINK_H
