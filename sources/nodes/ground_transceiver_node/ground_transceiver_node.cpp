#include "ground_transceiver_node.h"

// Qt
#include <QTimerEvent>
#include <QBasicTimer>
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_link.h"
#include "serial_port_link.h"

#include "ground_transmitter.h"
#include "ground_receiver.h"

#include "connection_status_packet.h"

using namespace domain;

class GroundTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;
    AbstractLink* activeLink = nullptr;

    QBasicTimer linkTimer;
    int linkInterval;

    GroundReceiver receiver;
    GroundTransmitter transmitter;
};

GroundTransceiverNode::GroundTransceiverNode(QObject* parent):
    AbstractNodeFrequency(Config::value("GroundTransceiver/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    Config::begin("GroundTransceiver");
    d->pub.bind(endpoints::groundGateway);
    connect(&d->receiver, &GroundReceiver::publish, &d->pub,
            static_cast<void(Publisher::*)(const QString&, const QByteArray&)>(
                &Publisher::publish));

    d->linkInterval = Config::value("link_timeout").toInt();

    d->wireLink = new UdpLink(
                      Config::value("udp_ground_port").toInt(),
                      QHostAddress(Config::value("udp_board_address").toString()),
                      Config::value("udp_board_port").toInt(), this);
    connect(d->wireLink, &AbstractLink::received,
            this, &GroundTransceiverNode::onWireLinkReceived);


    d->airLink = new SerialPortLink(
                     Config::value("serial_port_ground").toString(),
                     Config::value("serial_baud_rate").toInt(),
                     this);
    connect(d->airLink, &AbstractLink::received,
            this, &GroundTransceiverNode::onAirLinkReceived);

    Config::end();
}

GroundTransceiverNode::~GroundTransceiverNode()
{
    delete d;
}

void GroundTransceiverNode::init()
{
    d->sub.connectTo(endpoints::gui);
    d->sub.subscribe(topics::data);

    connect(&d->sub, &Subscriber::received,
            this, &GroundTransceiverNode::onSubReceived);
}

void GroundTransceiverNode::exec()
{
    // TODO: connect by user's request
    if (!d->wireLink->isConnected()) d->wireLink->connectLink();
    if (!d->airLink->isConnected()) d->airLink->connectLink();

    if (d->activeLink)
    {
        d->transmitter.transmit(d->activeLink);
    }
    else
    {
        d->transmitter.transmit(d->wireLink);
        d->transmitter.transmit(d->airLink);
    }

    ConnectionStatusPacket statusPacket; // TODO: connection packet to status packet

    statusPacket.airLink = d->activeLink == d->airLink;
    statusPacket.wireLink = d->activeLink == d->wireLink;
    statusPacket.packetsPerSecond = d->receiver.count() * this->frequency();
    statusPacket.packetsLost = (d->receiver.count()) ?
                                   100 * d->receiver.packetsLost() /
                                   d->receiver.count() : 0;

    d->receiver.reset();

    d->pub.publish(topics::connectionStatusPacket, statusPacket.toByteArray());
}

void GroundTransceiverNode::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == d->linkTimer.timerId())
    {
        d->activeLink = nullptr;
    }

    AbstractNodeFrequency::timerEvent(event);
}

void GroundTransceiverNode::onSubReceived(const QString& topic, const QByteArray& data)
{
    if (topic == topics::controlPacket) d->transmitter.setManualData(data);
    else if (topic == topics::automaticPacket) d->transmitter.setAutomaticData(data);
}

void GroundTransceiverNode::onWireLinkReceived(const QByteArray& data)
{
    d->activeLink = d->wireLink;
    d->linkTimer.start(d->linkInterval, Qt::PreciseTimer, this);
    d->receiver.onLinkReceived(data);
}

void GroundTransceiverNode::onAirLinkReceived(const QByteArray& data)
{
    d->activeLink = d->airLink;
    d->linkTimer.start(d->linkInterval, Qt::PreciseTimer, this);
    d->receiver.onLinkReceived(data);
}
