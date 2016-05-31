#ifndef SERIAL_PORT_LINK_H
#define SERIAL_PORT_LINK_H

#include "abstract_link.h"

class QSerialPort;

namespace domain
{
    class SerialPortLink: public AbstractLink
    {
        Q_OBJECT

    public:
        SerialPortLink(const QString& device, qint32 baudRate,
                       QObject* parent = nullptr);

        bool isConnected() const override;

    public slots:
        bool connectLink() override;
        void disconnectLink() override;
        void send(const QByteArray& packet) override;

    private slots:
        void readSerialData();
        void processFramgent(const QByteArray& fragment);

    private:
        QSerialPort* m_port;
        qint32 m_baudRate;
        QByteArray m_data;
    };
}

#endif // SERIAL_PORT_LINK_H
