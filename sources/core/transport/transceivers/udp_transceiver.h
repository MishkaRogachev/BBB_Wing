#ifndef UDP_TRANSCEIVER_H
#define UDP_TRANSCEIVER_H

#include "abstract_transceiver.h"

// Qt
#include <QtNetwork/QHostAddress>

class QUdpSocket;

namespace domain
{
    class UdpTransceiver: public AbstractTransceiver
    {
        Q_OBJECT

    public:
        UdpTransceiver(QHostAddress address, int port, QObject* parent = nullptr);

    public slots:
        void transmit(const QByteArray& packet) override;

    private:
        QUdpSocket* m_socket;
    };
}

#endif // UDP_TRANSCEIVER_H
