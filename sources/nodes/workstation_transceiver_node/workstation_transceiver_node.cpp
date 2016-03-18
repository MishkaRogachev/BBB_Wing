#include "workstation_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_transceiver.h"
#include "serial_port_transceiver.h"

#include "workstation_receiver_node.h"
#include "workstation_transmitter_node.h"

using namespace domain;

class WorkstationTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractTransceiver* wireTransceiver;
    AbstractTransceiver* airTransceiver;
    AbstractTransceiver* activeTransceiver = nullptr;

    WorkstationReceiverNode* receiver;
    WorkstationTransmitterNode* transmitter;
};

WorkstationTransceiverNode::WorkstationTransceiverNode(QObject* parent):
    BranchNode(parent),
    d(new Impl())
{
    Config::begin("Transceiver"); // TODO: unique board/workstation
    d->pub.bind("ipc://transceiver");

    d->wireTransceiver = new UdpTransceiver(
        QHostAddress(Config::setting("udp_workstation_address").toString()),
        Config::setting("udp_workstation_port").toInt(),
        QHostAddress(Config::setting("udp_board_address").toString()),
        Config::setting("udp_board_port").toInt(), this);
    connect(d->wireTransceiver, &AbstractTransceiver::received,
            this, &WorkstationTransceiverNode::onPacketReceived);

    d->airTransceiver = new SerialPortTransceiver(
        Config::setting("serial_port_workstation").toString(), this);
    connect(d->airTransceiver, &AbstractTransceiver::received,
            this, &WorkstationTransceiverNode::onPacketReceived);

    // 1 Hz for receive statistics & timeout
    d->receiver = new WorkstationReceiverNode(1, &d->pub);
    connect(d->receiver, &WorkstationReceiverNode::timeout,
            this, &WorkstationTransceiverNode::setInactiveLine);
    this->addNode(d->receiver);

    d->transmitter = new WorkstationTransmitterNode(1);
    connect(d->transmitter, &WorkstationTransmitterNode::transmit,
            this, &WorkstationTransceiverNode::transmitPacket);
    this->addNode(d->transmitter);

    Config::end();
}

WorkstationTransceiverNode::~WorkstationTransceiverNode()
{
    delete d;
}

void WorkstationTransceiverNode::init()
{
    BranchNode::init();

    d->sub.connectTo("ipc://ui");
    d->sub.subscribe("");

    connect(&d->sub, &Subscriber::received,
            d->transmitter, &WorkstationTransmitterNode::onSubReceived);
}

void WorkstationTransceiverNode::onPacketReceived(const QByteArray& packet)
{
    if (this->sender() == d->wireTransceiver)
    {
        this->setActiveWireLine();
        d->receiver->onPacketReceived(packet);
    }
    else if (this->sender() == d->airTransceiver &&
             d->activeTransceiver != d->wireTransceiver)
    {
        this->setActiveAirLine();
        d->receiver->onPacketReceived(packet);
    }
}

void WorkstationTransceiverNode::transmitPacket(const QByteArray& packet)
{
    if (!d->activeTransceiver) return;
    d->activeTransceiver->transmit(packet);
}

void WorkstationTransceiverNode::setActiveWireLine()
{
    d->activeTransceiver = d->wireTransceiver;
    d->pub.publish(topics::transceiverLine, "wire");
}

void WorkstationTransceiverNode::setActiveAirLine()
{
    d->activeTransceiver = d->airTransceiver;
    d->pub.publish(topics::transceiverLine, "air");
}

void WorkstationTransceiverNode::setInactiveLine()
{
    d->activeTransceiver = nullptr;
    d->pub.publish(topics::transceiverLine, "none");
}
