#include "udp_link.h"

// Qt
#include <QtNetwork/QUdpSocket>

using namespace domain;

UdpLink::UdpLink(int hostPort, const QHostAddress& adress, int port,
                 QObject* parent):
    AbstractLink(parent),
    m_socket(new QUdpSocket(this)),
    m_hostPort(hostPort),
    m_adress(adress),
    m_port(port)
{
    QObject::connect(m_socket, &QUdpSocket::readyRead,
                     this, &UdpLink::readPendingDatagrams);
}

QHostAddress UdpLink::adress() const
{
    return m_adress;
}

int UdpLink::port() const
{
    return m_port;
}

bool UdpLink::isConnected() const
{
    return m_socket->state() == QAbstractSocket::BoundState;
}

bool UdpLink::connectLink()
{
    if (m_socket->bind(m_hostPort)) return true;

    qWarning("UDP connection error: '%s'!",
             qPrintable(m_socket->errorString()));

    m_socket->close();
    return false;
}

void UdpLink::disconnectLink()
{
    m_socket->close();
}

void UdpLink::send(const QByteArray& packet)
{
    m_socket->writeDatagram(packet, m_adress, m_port);
}

void UdpLink::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray packet;
        packet.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(packet.data(), packet.size());

        emit received(packet);
    }
}

void UdpLink::setPort(int port)
{
    m_port = port;
}

void UdpLink::setAdress(const QHostAddress& adress)
{
    m_adress = adress;
}
