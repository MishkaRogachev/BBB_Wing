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

    QMap <QString, CrcPacket> packets;
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

    if (d->packets.isEmpty()) // TODO: blanking command or single direct packet
        d->packets.insert(topics::interview,
                          CrcPacket(topics::interview, QByteArray()));

    QList<AbstractLink*> links;

    for (const CrcPacket& packet: d->packets)
    {
        QByteArray data = packet.toByteArray();

        if (d->wireLink->isConnected() && (!d->airLink->isOnline() ||
            (d->wireLink->isOnline() && d->airLink->isOnline())))
            d->wireLink->send(data);

        if (d->airLink->isConnected() && !d->wireLink->isOnline())
            d->airLink->send(data);
    }

    d->packets.clear();

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
    d->packets.insert(topic, CrcPacket(topic, data));
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

    d->pub->publish(packet.topic, packet.data);
}

