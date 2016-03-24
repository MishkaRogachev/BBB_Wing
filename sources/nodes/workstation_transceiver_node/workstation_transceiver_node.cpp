#include "workstation_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_exchanger.h"
#include "serial_port_exchanger.h"

#include "workstation_receiver_node.h"
#include "workstation_transmitter_node.h"

using namespace domain;

class WorkstationTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractExchanger* wireLine;
    AbstractExchanger* airLine;
    AbstractExchanger* activeLine = nullptr;

    WorkstationReceiverNode* receiver;
    WorkstationTransmitterNode* transmitter;
};

WorkstationTransceiverNode::WorkstationTransceiverNode(QObject* parent):
    BranchNode(parent),
    d(new Impl())
{
    Config::begin("Transceiver"); // TODO: unique board/workstation
    d->pub.bind("ipc://transceiver");

    d->wireLine = new UdpExchanger(
        Config::setting("udp_workstation_port").toInt(),
        QHostAddress(Config::setting("udp_board_address").toString()),
        Config::setting("udp_board_port").toInt(), this);
    connect(d->wireLine, &AbstractExchanger::received,
            this, &WorkstationTransceiverNode::onPacketReceived);
    d->wireLine->start();

    d->airLine = new SerialPortExchanger(
        Config::setting("serial_port_workstation").toString(), this);
    connect(d->airLine, &AbstractExchanger::received,
            this, &WorkstationTransceiverNode::onPacketReceived);
    d->airLine->start();

    // 1 Hz for receive statistics & timeout
    d->receiver = new WorkstationReceiverNode(1, &d->pub);
    connect(d->receiver, &WorkstationReceiverNode::timeout,
            this, &WorkstationTransceiverNode::setLineInactive);
    this->addNode(d->receiver);

    d->transmitter = new WorkstationTransmitterNode(
                         Config::setting("transmitter_frequency").toInt());
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
    if (this->sender() == d->wireLine)
    {
        this->setActiveWireLine();
    }
    else if (d->activeLine != d->wireLine)
    {
        this->setActiveAirLine();
    }

    d->receiver->processPacket(packet);
}

void WorkstationTransceiverNode::transmitPacket(const QByteArray& packet)
{
    if (d->activeLine)
    {
        d->activeLine->transmit(packet);
    }
    else
    {
        d->wireLine->transmit(packet);
        d->airLine->transmit(packet);
    }
}

void WorkstationTransceiverNode::setActiveWireLine()
{
    d->activeLine = d->wireLine;
    d->pub.publish(topics::transceiverLine, "wire");
}

void WorkstationTransceiverNode::setActiveAirLine()
{
    d->activeLine = d->airLine;
    d->pub.publish(topics::transceiverLine, "air");
}

void WorkstationTransceiverNode::setLineInactive()
{
    d->activeLine = nullptr;
    d->pub.publish(topics::transceiverLine, "none");
}
