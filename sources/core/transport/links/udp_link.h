#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "abstract_link.h"

// Qt
#include <QtNetwork/QHostAddress>

class QUdpSocket;

namespace domain
{
    class UdpLink: public AbstractLink
    {
        Q_OBJECT

    public:
        UdpLink(int hostPort, const QHostAddress& adress, int port,
                     QObject* parent = nullptr);

        QHostAddress adress() const;
        int port() const;
        bool isAvailable() const override;

    public slots:
        bool start() override;
        void transmit(const QByteArray& packet) override;

        void setAdress(const QHostAddress& adress);
        void setPort(int port);

    private slots:
        void readPendingDatagrams();

    private:
        QUdpSocket* m_socket;
        int m_hostPort;
        QHostAddress m_adress;
        int m_port;
    };
}

#endif // UDP_LINK_H
