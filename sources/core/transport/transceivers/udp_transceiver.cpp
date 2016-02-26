#include "udp_transceiver.h"

// Qt
#include <QtNetwork/QUdpSocket>

using namespace domain;

UdpTransceiver::UdpTransceiver(QHostAddress address, int port, QObject* parent):
    AbstractTransceiver(parent),
    m_socket(new QUdpSocket(this))
{
    m_socket->bind(address, port);
}

void UdpTransceiver::transmit(const QByteArray& packet)
{

}
