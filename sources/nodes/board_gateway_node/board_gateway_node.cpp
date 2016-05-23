#include "board_gateway_node.h"

// Qt
#include <QMap>
#include <QTimer>
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_link.h"
#include "serial_port_link.h"

#include "crc_packet.h"
#include "reverse_packet.h"

using namespace domain;

class BoardGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;

    ReversePacket packet;

    QTimer* altTimer;
    QTimer* insTimer;
    QTimer* snsTimer;
    QTimer* controlTimer;
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
                     Config::value("serial_port_board").toString(),
                     Config::value("serial_baud_rate").toInt(),
                     this);
    connect(d->airLink, &AbstractLink::received,
            this, &BoardGatewayNode::onLinkReceived);

    d->altTimer = new QTimer(this);
    d->altTimer->setInterval(Config::value("alt_timeout").toInt());
    connect(d->altTimer, &QTimer::timeout, this, &BoardGatewayNode::onAltTimeout);

    d->insTimer = new QTimer(this);
    d->insTimer->setInterval(Config::value("ins_timeout").toInt());
    connect(d->insTimer, &QTimer::timeout, this, &BoardGatewayNode::onInsTimeout);

    d->snsTimer = new QTimer(this);
    d->snsTimer->setInterval(Config::value("sns_timeout").toInt());
    connect(d->snsTimer, &QTimer::timeout, this, &BoardGatewayNode::onSnsTimeout);

    d->controlTimer = new QTimer(this);
    d->controlTimer->setInterval(Config::value("ctrl_timeout").toInt());
    connect(d->controlTimer, &QTimer::timeout, this, &BoardGatewayNode::onControlTimeout);

    Config::end();

    this->onAltTimeout();
    this->onInsTimeout();
    this->onSnsTimeout();
    this->onControlTimeout();
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
                       endpoints::navigator,
                       endpoints::flightPilot });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &BoardGatewayNode::onSubReceived);
}

void BoardGatewayNode::exec()
{
    if (!d->wireLink->isConnected()) d->wireLink->connect();
    if (!d->airLink->isConnected()) d->airLink->connect();

    CrcPacket crcPacket(topics::reversePacket, d->packet.toByteArray());
    QByteArray data = crcPacket.toByteArray();

    if (d->wireLink->isConnected() && d->wireLink->isOnline())
        d->wireLink->send(data);
    if (d->airLink->isConnected() && d->airLink->isOnline())
        d->airLink->send(data);
}

void BoardGatewayNode::onSubReceived(const QString& topic, const QByteArray& data)
{
    if (topic == topics::altPacket)
    {
        d->packet.alt = AltPacket::fromByteArray(data);
        d->packet.altAvalible = true;
        d->altTimer->start();
    }
    else if (topic == topics::insPacket)
    {
        d->packet.ins = InsPacket::fromByteArray(data);
        d->packet.insAvalible = true;
        d->insTimer->start();
    }
    else if (topic == topics::snsPacket)
    {
        d->packet.sns = SnsPacket::fromByteArray(data);
        d->packet.snsAvalible = true;
        d->snsTimer->start();
    }
    else if (topic == topics::controlPacket)
    {
        d->packet.control = ControlPacket::fromByteArray(data);
        d->packet.controlAvalible = true;
        d->controlTimer->start();
    }
}

void BoardGatewayNode::onLinkReceived(const QByteArray& data)
{
    auto packet = CrcPacket::fromByteArray(data);
    if (!packet.validateCrc()) return;

    d->pub.publish(packet.topic, packet.data);
}

void BoardGatewayNode::onAltTimeout()
{
    d->packet.altAvalible = false;
}

void BoardGatewayNode::onInsTimeout()
{
    d->packet.insAvalible = false;
}

void BoardGatewayNode::onSnsTimeout()
{
    d->packet.snsAvalible = false;
}

void BoardGatewayNode::onControlTimeout()
{
    d->packet.controlAvalible = false;
}
