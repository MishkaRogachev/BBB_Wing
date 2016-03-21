#include "udp_exchanger.h"

// Qt
#include <QtNetwork/QUdpSocket>

using namespace domain;

UdpExchanger::UdpExchanger(int hostPort, const QHostAddress& adress, int port,
                               QObject* parent):
    AbstractExchanger(parent),
    m_socket(new QUdpSocket(this)),
    m_hostPort(hostPort),
    m_adress(adress),
    m_port(port)
{
    connect(m_socket, &QUdpSocket::readyRead, this,
            &UdpExchanger::readPendingDatagrams);
}

QHostAddress UdpExchanger::adress() const
{
    return m_adress;
}

int UdpExchanger::port() const
{
    return m_port;
}

bool UdpExchanger::isAvailable() const
{
    return m_socket->isOpen(); // TODO: handle socket avalibility
}

bool UdpExchanger::start()
{
    return m_socket->bind(m_hostPort);
}

void UdpExchanger::transmit(const QByteArray& packet)
{
    m_socket->writeDatagram(packet, m_adress, m_port);
}

void UdpExchanger::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray packet;
        packet.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(packet.data(), packet.size());

        emit received(packet);
    }
}

void UdpExchanger::setPort(int port)
{
    m_port = port;
}

void UdpExchanger::setAdress(const QHostAddress& adress)
{
    m_adress = adress;
}
