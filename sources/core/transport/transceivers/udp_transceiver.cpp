#include "udp_transceiver.h"

// Qt
#include <QtNetwork/QUdpSocket>

using namespace domain;

UdpTransceiver::UdpTransceiver(int port, const QHostAddress& transmitAdress, int transmitPort,
                               QObject* parent):
    AbstractTransceiver(parent),
    m_socket(new QUdpSocket(this)),
    m_port(port),
    m_transmitAdress(transmitAdress),
    m_transmitPort(transmitPort)
{
    connect(m_socket, &QUdpSocket::readyRead, this,
            &UdpTransceiver::readPendingDatagrams);
}

void UdpTransceiver::transmit(const QByteArray& packet)
{
    m_socket->writeDatagram(packet, m_transmitAdress, m_transmitPort);
}

bool UdpTransceiver::isAvailable() const
{
    return true; //TODO: isAvailable handling
}

QHostAddress UdpTransceiver::transmitAdress() const
{
    return m_transmitAdress;
}

int UdpTransceiver::transmitPort() const
{
    return m_transmitPort;
}

bool UdpTransceiver::start()
{
    return m_socket->bind(m_port);
}

void UdpTransceiver::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray packet;
        packet.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(packet.data(), packet.size());

        emit received(packet);
    }
}

void UdpTransceiver::setTransmitPort(int transmitPort)
{
    m_transmitPort = transmitPort;
}

void UdpTransceiver::setTransmitAdress(const QHostAddress& transmitAdress)
{
    m_transmitAdress = transmitAdress;
}
