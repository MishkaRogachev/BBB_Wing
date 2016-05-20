#include "ground_gateway_node.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_link.h"
#include "serial_port_link.h"

#include "crc_packet.h"
#include "connection_status_packet.h"
#include "direct_packet.h"
#include "reverse_packet.h"

using namespace domain;

class GroundGatewayNode::Impl
{
public:
    Subscriber* sub;
    Publisher* pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;

    int count = 0;
    int packetsLost = 0;

    DirectPacket packet;
};

GroundGatewayNode::GroundGatewayNode(QObject* parent):
    AbstractNodeFrequency(Config::value("GroundGateway/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->sub = new Subscriber(this);
    d->pub = new Publisher(this);

    Config::begin("GroundGateway");
    d->pub->bind(endpoints::groundGateway);

    d->wireLink = new UdpLink(
                      Config::value("udp_ground_port").toInt(),
                      QHostAddress(Config::value("udp_board_address").toString()),
                      Config::value("udp_board_port").toInt(), this);
    connect(d->wireLink, &AbstractLink::received,
            this, &GroundGatewayNode::onLinkReceived);

    d->airLink = new SerialPortLink(
                     Config::value("serial_port_ground").toString(),
                     Config::value("serial_baud_rate").toInt(),
                     this);
    connect(d->airLink, &AbstractLink::received,
            this, &GroundGatewayNode::onLinkReceived);

    Config::end();
}

GroundGatewayNode::~GroundGatewayNode()
{
    delete d;
}

void GroundGatewayNode::init()
{
     d->sub->connectTo(endpoints::gui);
     d->sub->subscribe(topics::data);

     connect(d->sub, &Subscriber::received,
             this, &GroundGatewayNode::onSubReceived);
}

void GroundGatewayNode::exec()
{
    // TODO: connect by user's request
    if (!d->wireLink->isConnected()) d->wireLink->connect();
    if (!d->airLink->isConnected()) d->airLink->connect();

    CrcPacket crcPacket(topics::directPacket, d->packet.toByteArray());
    QByteArray data = crcPacket.toByteArray();

    if (d->wireLink->isConnected() && (!d->airLink->isOnline() ||
        (d->airLink->isOnline() && d->wireLink->isOnline())))
        d->wireLink->send(data);

    if (d->airLink->isConnected() && !d->wireLink->isOnline())
        d->airLink->send(data);

    ConnectionStatusPacket statusPacket;

    statusPacket.airLink = d->airLink->isOnline();
    statusPacket.wireLink = d->wireLink->isOnline();
    statusPacket.packetsPerSecond = d->count * this->frequency();
    statusPacket.packetsLost = (d->count) ? 100 * d->packetsLost / d->count : 0;

    d->pub->publish(topics::connectionStatusPacket, statusPacket.toByteArray());

    d->count = 0;
    d->packetsLost = 0;
}

void GroundGatewayNode::stop()
{
    d->airLink->disconnect();
    d->wireLink->disconnect();

    AbstractNodeFrequency::stop();
}

void GroundGatewayNode::onSubReceived(const QString& topic,
                                     const QByteArray& data)
{
    if (topic == topics::directPacket)
    {
        d->packet = DirectPacket::fromByteArray(data);
    }
}

void GroundGatewayNode::onLinkReceived(const QByteArray& data)
{
    d->count++;

    auto packet = CrcPacket::fromByteArray(data);
    if (!packet.validateCrc())
    {
        d->packetsLost++;
        return;
    }

    if (packet.topic == topics::reversePacket)
    {
        ReversePacket packet = ReversePacket::fromByteArray(data);

        if (packet.altAvalible)
            d->pub->publish(topics::altPacket, packet.alt.toByteArray());

        if (packet.insAvalible)
            d->pub->publish(topics::insPacket, packet.ins.toByteArray());

        if (packet.snsAvalible)
            d->pub->publish(topics::snsPacket, packet.sns.toByteArray());

        if (packet.controlAvalible)
            d->pub->publish(topics::controlPacket, packet.control.toByteArray());
    }
}

