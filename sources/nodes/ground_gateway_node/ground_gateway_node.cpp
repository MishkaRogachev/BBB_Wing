#include "ground_gateway_node.h"

// Qt
#include <QTimer>
#include <QMap>
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_exchanger.h"
#include "serial_port_exchanger.h"

#include "connection_status_packet.h"
#include "transmission_packet.h"

using namespace domain;

class GroundGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractExchanger* wireLine;
    AbstractExchanger* airLine;

    QTimer* timoutTimer;

    bool wireReceived = false;
    bool airReceived = false;
    int count = 0;
    int badCount = 0;

    QMap <QString, QByteArray> dataMap;
};

GroundGatewayNode::GroundGatewayNode(QObject* parent):
    AbstractNodeFrequency(0, parent),
    d(new Impl())
{
    Config::begin("GroundGateway");
    d->pub.bind("ipc://ground_gateway");

    this->setFrequency(Config::value("frequency").toFloat());

    d->wireLine = new UdpExchanger(
                      Config::value("udp_ground_port").toInt(),
                      QHostAddress(Config::value("udp_board_address").toString()),
                      Config::value("udp_board_port").toInt(), this);
    connect(d->wireLine, &AbstractExchanger::received,
            this, &GroundGatewayNode::onLineReceived);

    d->airLine = new SerialPortExchanger(
                     Config::value("serial_port_ground").toString(), this);
    connect(d->airLine, &AbstractExchanger::received,
            this, &GroundGatewayNode::onLineReceived);

    d->timoutTimer = new QTimer(this);
    d->timoutTimer->setInterval(Config::value("timeout_interval").toInt());
    d->timoutTimer->setSingleShot(true);
    connect(d->timoutTimer, &QTimer::timeout, this, &GroundGatewayNode::onTimeout);

    Config::end();
}

GroundGatewayNode::~GroundGatewayNode()
{
    delete d;
}

void GroundGatewayNode::init()
{
     d->sub.connectTo("ipc://ui");
     d->sub.subscribe(topics::data);
}

void GroundGatewayNode::start()
{
    AbstractNodeFrequency::start();

    d->wireLine->start();
    d->airLine->start();

    connect(&d->sub, &Subscriber::received, this,
            &GroundGatewayNode::onSubReceived);
}

void GroundGatewayNode::exec()
{
    if (d->dataMap.isEmpty())
        d->dataMap.insert("interview", QByteArray::number(true));// TODO: interview board
    for (const QString& topic: d->dataMap)
    {
        TransmissionPacket packet;

        packet.topic = topic;
        packet.data = d->dataMap[topic];
        packet.calcCrc();

        if (!d->airReceived || (d->wireReceived && d->airReceived))
            d->wireLine->transmit(packet.toByteArray());
        if (!d->wireReceived)
            d->airLine->transmit(packet.toByteArray());
    }

    d->dataMap.clear();

    ConnectionStatusPacket statusPacket;

    statusPacket.airLine = d->airReceived;
    statusPacket.wireLine = d->wireReceived;
    statusPacket.packetsPerSecond = d->count * this->frequency();
    statusPacket.badPackets = (d->count) ? 100 * d->badCount / d->count : 0;

    d->pub.publish(topics::connectionStatusPacket, statusPacket.toByteArray());

    d->count = 0;
    d->badCount = 0;
}

void GroundGatewayNode::onTimeout()
{
    d->wireReceived = false;
    d->airReceived = false;
}

void GroundGatewayNode::onSubReceived(const QString& topic,
                                     const QByteArray& data)
{
    d->dataMap[topic] = data;
}

void GroundGatewayNode::onLineReceived(const QByteArray& data)
{
    if (this->sender() == d->wireLine) d->wireReceived = true;
    else if (this->sender() == d->airLine) d->airReceived = true;
    d->count++;

    auto packet = TransmissionPacket::fromByteArray(data);
    if (!packet.validateCrc())
    {
        d->badCount++;
        return;
    }

    d->pub.publish(packet.topic, packet.data);
    d->timoutTimer->start();
}

