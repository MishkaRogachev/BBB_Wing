#include "serial_port_transceiver.h"

// Qt
#include <QtSerialPort/QSerialPort>

using namespace domain;

SerialPortTransceiver::SerialPortTransceiver(const QString& device,
                                             QObject* parent):
    AbstractTransceiver(parent)
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
    while (!m_port->atEnd())
    {
        QByteArray data = m_port->readAll();
        emit received(data);
    }
}
