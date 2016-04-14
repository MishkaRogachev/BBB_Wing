#include "serial_port_link.h"

// Qt
#include <QtSerialPort/QSerialPort>
#include <QDebug>

namespace
{
    const QByteArray separator = QByteArray::fromHex("A0BC1F0923");
}

using namespace domain;

SerialPortLink::SerialPortLink(const QString& device, QObject* parent):
    AbstractLink(parent)
{
    m_port = new QSerialPort(device, this);

    QObject::connect(m_port, &QSerialPort::readyRead,
                     this, &SerialPortLink::readSerialData);
}

bool SerialPortLink::isConnected() const
{
    return m_port->isOpen(); // TODO: handle serial port avalibility
}

bool SerialPortLink::connect()
{
    if (m_port->open(QIODevice::ReadWrite))
    {
    // m_port->setBaudRate(38400); TODO: setBaudRate, after hardware reconfiguration
        return true;
    }

    m_port->close();
    return false;
}

void SerialPortLink::disconnect()
{
    m_port->close();
}

void SerialPortLink::send(const QByteArray& packet)
{
    m_port->write(::separator);
    m_port->write(packet.data(), packet.size());
}

void SerialPortLink::readSerialData()
{
    m_data.append(m_port->readAll());

    if (!m_data.contains(::separator)) return;

    for (int start = 0;;)
    {
        int pos = m_data.indexOf(::separator, start) + ::separator.length();
        if (pos == -1 || pos < start)
        {
            m_data = m_data.right(m_data.size() - start);
            return;
        }

        this->processFramgent(m_data.mid(start, pos - start - ::separator.length()));
        start = pos;
    }
}

void SerialPortLink::processFramgent(const QByteArray& fragment)
{
    if (fragment.isEmpty()) return;
    this->onReceived(fragment);
}
