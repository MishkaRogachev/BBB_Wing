#include "gateway_node.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "subscriber.h"
#include "publisher.h"

#include "abstract_link.h"
#include "crc_packet.h"

using namespace domain;

class GatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    QList<AbstractLink*> links;
    QMap<QString, CrcPacket> packets;
};

GatewayNode::GatewayNode(const QString& endpoint, float frequency,
                         QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind(endpoint);

    connect(&d->sub, &Subscriber::received, this,
            &GatewayNode::onSubReceived);
}

GatewayNode::~GatewayNode()
{
    delete d;
}

void GatewayNode::addLink(AbstractLink* link)
{
    d->links.append(link);
    connect(link, &AbstractLink::received, this, &GatewayNode::onLinkReceived);
}

void GatewayNode::removeLink(AbstractLink* link)
{
     d->links.removeOne(link);
     disconnect(link, &AbstractLink::received, this, &GatewayNode::onLinkReceived);
}

void GatewayNode::subscribe(const QStringList& enpoints, const QStringList& topics)
{
    d->sub.connectTo(enpoints);
    d->sub.subscribe(topics);
}

void GatewayNode::exec()
{
    for (const CrcPacket& packet: d->packets.values())
        this->transmit(packet.toByteArray());

    d->packets.clear();
}

void GatewayNode::transmit(const QByteArray& data)
{
    for (AbstractLink* link: d->links)
    {
        if (link->isConnected()) link->transmit(data);
    }
}

void GatewayNode::onSubReceived(const QString& topic, const QByteArray& data)
{
    d->packets.insert(topic, CrcPacket(topic, data));
}

void GatewayNode::onLinkReceived(const QByteArray& data)
{
    CrcPacket packet = CrcPacket::fromByteArray(data);
    if (!packet.validateCrc()) return;

    d->pub.publish(packet.topic, packet.data);
}
