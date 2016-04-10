#include "ground_gateway_node.h"

// Qt
#include <QTimer>
#include <QMap>
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_link.h"
#include "serial_port_link.h"

#include "connection_status_packet.h"
#include "transmission_packet.h"

using namespace domain;

class GroundGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;

    QTimer* timoutTimer;

    bool wireReceived = false;
    bool airReceived = false;
    int count = 0;
    int badCount = 0;

    QMap <QString, QByteArray> dataMap;
};

GroundGatewayNode::GroundGatewayNode(QObject* parent):
    AbstractNodeFrequency(Config::value("GroundGateway/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    Config::begin("GroundGateway");
    d->pub.bind(endpoints::groundGateway);

    d->wireLink = new UdpLink(
                      Config::value("udp_ground_port").toInt(),
                      QHostAddress(Config::value("udp_board_address").toString()),
                      Config::value("udp_board_port").toInt(), this);
    connect(d->wireLink, &AbstractLink::received,
            this, &GroundGatewayNode::onLinkReceived);

    d->airLink = new SerialPortLink(
                     Config::value("serial_port_ground").toString(), this);
    connect(d->airLink, &AbstractLink::received,
            this, &GroundGatewayNode::onLinkReceived);

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
     d->sub.connectTo(endpoints::gui);
     d->sub.subscribe(topics::data);
}

void GroundGatewayNode::start()
{
    AbstractNodeFrequency::start();

    d->wireLink->connect();
    d->airLink->connect();

    connect(&d->sub, &Subscriber::received, this,
            &GroundGatewayNode::onSubReceived);
}

void GroundGatewayNode::exec()
{
    if (d->dataMap.isEmpty())
        d->dataMap.insert(topics::interview, QByteArray());

    for (const QString& topic: d->dataMap)
    {
        TransmissionPacket packet;

        packet.topic = topic;
        packet.data = d->dataMap[topic];
        packet.calcCrc();

        if (!d->airReceived || (d->wireReceived && d->airReceived))
            d->wireLink->tryTransmit(packet.toByteArray());
        if (!d->wireReceived)
            d->airLink->tryTransmit(packet.toByteArray());
    }

    d->dataMap.clear();

    ConnectionStatusPacket statusPacket;

    statusPacket.airLink = d->airReceived;
    statusPacket.wireLink = d->wireReceived;
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
    d->dataMap.insert(topic, data);
}

void GroundGatewayNode::onLinkReceived(const QByteArray& data)
{
    if (this->sender() == d->wireLink) d->wireReceived = true;
    else if (this->sender() == d->airLink) d->airReceived = true;
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

