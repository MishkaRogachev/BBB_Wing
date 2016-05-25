#include "board_transceiver_node.h"

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

#include "board_transmitter.h"
#include "board_receiver.h"

using namespace domain;

class BoardTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractLink* wireLink;
    AbstractLink* airLink;
    AbstractLink* activeLink = nullptr;

    QBasicTimer linkTimer;
    int linkInterval;

    BoardReceiver receiver;
    BoardTransmitter transmitter;
};

BoardTransceiverNode::BoardTransceiverNode(QObject* parent):
    AbstractNodeFrequency(Config::value("BoardTransceiver/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    Config::begin("BoardTransceiver");
    d->pub.bind(endpoints::boardGateway);
    connect(&d->receiver, &BoardReceiver::publish, &d->pub,
            static_cast<void(Publisher::*)(const QString&, const QByteArray&)>(
                &Publisher::publish));

    d->linkInterval = Config::value("link_timeout").toInt();

    d->wireLink = new UdpLink(
                      Config::value("udp_board_port").toInt(),
                      QHostAddress(Config::value("udp_ground_address").toString()),
                      Config::value("udp_ground_port").toInt(), this);
    connect(d->wireLink, &AbstractLink::received,
            this, &BoardTransceiverNode::onWireLinkReceived);

    d->airLink = new SerialPortLink(
                     Config::value("serial_port_board").toString(),
                     Config::value("serial_baud_rate").toInt(),
                     this);
    connect(d->airLink, &AbstractLink::received,
            this, &BoardTransceiverNode::onAirLinkReceived);

    Config::end();
}

BoardTransceiverNode::~BoardTransceiverNode()
{
    delete d;
}

void BoardTransceiverNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::flightPilot });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &BoardTransceiverNode::onSubReceived);
}

void BoardTransceiverNode::exec()
{
    if (!d->wireLink->isConnected()) d->wireLink->connectLink();
    if (!d->airLink->isConnected()) d->airLink->connectLink();

    if (d->activeLink) d->transmitter.transmit(d->activeLink);
}

void BoardTransceiverNode::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == d->linkTimer.timerId())
    {
        d->activeLink = nullptr;
    }

    AbstractNodeFrequency::timerEvent(event);
}

void BoardTransceiverNode::onSubReceived(const QString& topic, const QByteArray& data)
{
    if (topic == topics::altPacket) d->transmitter.setAltData(data);
    else if (topic == topics::insPacket) d->transmitter.setInsData(data);
    else if (topic == topics::snsPacket) d->transmitter.setSnsData(data);
    else if (topic == topics::controlPacket) d->transmitter.setControlData(data);
}

void BoardTransceiverNode::onWireLinkReceived(const QByteArray& data)
{
    d->activeLink = d->wireLink;
    d->linkTimer.start(d->linkInterval, Qt::PreciseTimer, this);
    d->receiver.onLinkReceived(data);
}

void BoardTransceiverNode::onAirLinkReceived(const QByteArray& data)
{
    d->activeLink = d->airLink;
    d->linkTimer.start(d->linkInterval, Qt::PreciseTimer, this);
    d->receiver.onLinkReceived(data);
}
