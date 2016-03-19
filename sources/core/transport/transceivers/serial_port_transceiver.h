#ifndef SERIAL_PORT_TRANSCEIVER_H
#define SERIAL_PORT_TRANSCEIVER_H

#include "abstract_transceiver.h"

class QSerialPort;

namespace domain
{
    class SerialPortTransceiver: public AbstractTransceiver
    {
        Q_OBJECT

    public:
        SerialPortTransceiver(const QString& device, QObject* parent = nullptr);

    public slots:
        bool start() override;
        void transmit(const QByteArray& packet) override;
        bool isAvailable() const override;

    private slots:
        void readSerialData();
        void processFramgent(const QByteArray& fragment);

    private:
        QSerialPort* m_port;
        QByteArray m_data;
    };
}

#endif // SERIAL_PORT_TRANSCEIVER_H
