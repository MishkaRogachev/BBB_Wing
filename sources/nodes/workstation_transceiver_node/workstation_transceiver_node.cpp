#include "workstation_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "workstation_receiver_node.h"

#include "udp_transceiver.h"
#include "serial_port_transceiver.h"

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
//    WorkstationTransmitterNode* transmitter; TODO: transmitter
};

WorkstationTransceiverNode::WorkstationTransceiverNode(QObject* parent):
    BranchNode(parent),
    d(new Impl())
{
    Config::begin("Transceiver");
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
    d->receiver = new WorkstationReceiverNode(1, &d->pub, this);
    connect(d->receiver, &WorkstationReceiverNode::timeout,
            this, &WorkstationTransceiverNode::setInactiveLine);
    this->addNode(d->receiver);

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

//    connect(&d->sub, &Subscriber::received, d->transmitter,
//                 &WorkstationTransmitterNode::onReceived);
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
