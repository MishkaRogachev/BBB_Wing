#include "board_gateway_node.h"

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

#include "transmission_packet.h"

using namespace domain;

class BoardGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;

    QTimer* timoutTimer;

    bool wireReceived = false;
    bool airReceived = false;
    QMap <QString, QByteArray> dataMap;
};

BoardGatewayNode::BoardGatewayNode(QObject* parent):
    AbstractNodeFrequency(Config::value("BoardGateway/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    Config::begin("BoardGateway");
    d->pub.bind(endpoints::boardGateway);

    d->wireLink = new UdpLink(
                      Config::value("udp_board_port").toInt(),
                      QHostAddress(Config::value("udp_ground_address").toString()),
                      Config::value("udp_ground_port").toInt(), this);
    connect(d->wireLink, &AbstractLink::received,
            this, &BoardGatewayNode::onLinkReceived);

    d->airLink = new SerialPortLink(
                     Config::value("serial_port_board").toString(), this);
    connect(d->airLink, &AbstractLink::received,
            this, &BoardGatewayNode::onLinkReceived);

    d->timoutTimer = new QTimer(this);
    d->timoutTimer->setInterval(Config::value("timeout_interval").toInt());
    d->timoutTimer->setSingleShot(true);
    connect(d->timoutTimer, &QTimer::timeout, this, &BoardGatewayNode::onTimeout);

    Config::end();
}

BoardGatewayNode::~BoardGatewayNode()
{
    delete d;
}

void BoardGatewayNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::failuresHandler,
                       endpoints::navigator,
                       endpoints::controller });

    d->sub.subscribe(topics::data);
}

void BoardGatewayNode::start()
{
    AbstractNodeFrequency::start();

    d->wireLink->connect();
    d->airLink->connect();

    connect(&d->sub, &Subscriber::received, this,
            &BoardGatewayNode::onSubReceived);
}

void BoardGatewayNode::exec()
{
    for (const QString& topic: d->dataMap.keys())
    {
        TransmissionPacket packet;

        packet.topic = topic;
        packet.data = d->dataMap[topic];
        packet.calcCrc();

        if (d->wireReceived) d->wireLink->tryTransmit(packet.toByteArray());
        if (d->airReceived) d->airLink->tryTransmit(packet.toByteArray());
    }

    d->dataMap.clear();
}

void BoardGatewayNode::onTimeout()
{
    d->wireReceived = false;
    d->airReceived = false;
}

void BoardGatewayNode::onSubReceived(const QString& topic,
                                     const QByteArray& data)
{
    d->dataMap[topic] = data;
}

void BoardGatewayNode::onLinkReceived(const QByteArray& data)
{
    if (this->sender() == d->wireLink) d->wireReceived = true;
    else if (this->sender() == d->airLink) d->airReceived = true;

    auto packet = TransmissionPacket::fromByteArray(data);
    if (!packet.validateCrc()) return;

    if (packet.topic == topics::interview)
        d->timoutTimer->start();
    else
        d->pub.publish(packet.topic, packet.data);
}
