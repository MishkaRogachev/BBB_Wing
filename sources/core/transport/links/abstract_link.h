#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

#include <QObject>

class QTimer;

namespace domain
{
    class AbstractLink: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractLink(QObject* parent = nullptr);
        ~AbstractLink() override;

        virtual bool isConnected() const = 0;
        bool isOnline() const;

    public slots:
        virtual bool connect() = 0;
        virtual void disconnect() = 0;
        virtual void send(const QByteArray& packet) = 0;

    signals:
        void received(const QByteArray& packet);
        void timeout();

    protected slots:
        void onReceived(const QByteArray& packet);
        void onTimeout();

    private:
        bool m_online;
        QTimer* m_timer;

        Q_DISABLE_COPY(AbstractLink)
    };
}

#endif // ABSTRACT_LINK_H
