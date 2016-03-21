#ifndef SERIAL_PORT_EXCHANGER_H
#define SERIAL_PORT_EXCHANGER_H

#include "abstract_exchanger.h"

class QSerialPort;

namespace domain
{
    class SerialPortExchanger: public AbstractExchanger
    {
        Q_OBJECT

    public:
        SerialPortExchanger(const QString& device, QObject* parent = nullptr);

        bool isAvailable() const override;

    public slots:
        bool start() override;
        void transmit(const QByteArray& packet) override;

    private slots:
        void readSerialData();
        void processFramgent(const QByteArray& fragment);

    private:
        QSerialPort* m_port;
        QByteArray m_data;
    };
}

#endif // SERIAL_PORT_EXCHANGER_H
