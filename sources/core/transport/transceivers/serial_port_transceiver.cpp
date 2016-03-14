#include "serial_port_transceiver.h"

// Qt
#include <QtSerialPort/QSerialPort>

using namespace domain;

SerialPortTransceiver::SerialPortTransceiver(const QString& device,
                                             int packetSize,
                                             QObject* parent):
    AbstractTransceiver(parent),
    m_packetSize(packetSize)
{
    m_port = new QSerialPort(device, this);
    m_port->open(QIODevice::ReadWrite);
    connect(m_port, &QSerialPort::readyRead,
            this, &SerialPortTransceiver::readSerialData);
}

void SerialPortTransceiver::transmit(const QByteArray& packet)
{
    m_port->write(packet.data(), packet.size());
}

void SerialPortTransceiver::readSerialData()
{
    m_data.append(m_port->readAll());

    if (m_data.size() >= m_packetSize)
    {
        emit received(m_data);
        m_data.clear();
    }
}
