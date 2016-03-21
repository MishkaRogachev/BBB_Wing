#ifndef UDP_EXCHANGER_H
#define UDP_EXCHANGER_H

#include "abstract_exchanger.h"

// Qt
#include <QtNetwork/QHostAddress>

class QUdpSocket;

namespace domain
{
    class UdpExchanger: public AbstractExchanger
    {
        Q_OBJECT

    public:
        UdpExchanger(int hostPort, const QHostAddress& adress, int port,
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

#endif // UDP_EXCHANGER_H
