#include "board_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_exchanger.h"
#include "serial_port_exchanger.h"

#include "board_receiver_node.h"
#include "board_transmitter_node.h"

using namespace domain;

class BoardTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractExchanger* wireLine;
    AbstractExchanger* airLine;
    AbstractExchanger* activeLine = nullptr;

    BoardReceiverNode* receiver;
    BoardTransmitterNode* transmitter;
};

BoardTransceiverNode::BoardTransceiverNode(QObject* parent):
    BranchNode(parent),
    d(new Impl())
{
    Config::begin("Transceiver");
    d->pub.bind("ipc://transceiver");

    d->wireLine = new UdpExchanger(
        Config::setting("udp_board_port").toInt(),
        QHostAddress(Config::setting("udp_workstation_address").toString()),
        Config::setting("udp_workstation_port").toInt(), this);
    connect(d->wireLine, &AbstractExchanger::received,
            this, &BoardTransceiverNode::onPacketReceived);
    d->wireLine->start();

    d->airLine = new SerialPortExchanger(
        Config::setting("serial_port_board").toString(), this);
    connect(d->airLine, &AbstractExchanger::received,
            this, &BoardTransceiverNode::onPacketReceived);
    d->airLine->start();

    // 1 Hz for timeout
    d->receiver = new BoardReceiverNode(1, &d->pub);
    connect(d->receiver, &BoardReceiverNode::timeout,
            this, &BoardTransceiverNode::onTimeout);
    this->addNode(d->receiver);

    d->transmitter = new BoardTransmitterNode(
                         Config::setting("transmitter_frequency").toInt());
    connect(d->transmitter, &BoardTransmitterNode::transmit,
            this, &BoardTransceiverNode::transmitPacket);
    this->addNode(d->transmitter);

    Config::end();
}

BoardTransceiverNode::~BoardTransceiverNode()
{
    delete d;
}

void BoardTransceiverNode::init()
{
     d->sub.connectTo("ipc://altimeter");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");

     connect(&d->sub, &Subscriber::received,
             d->transmitter, &BoardTransmitterNode::onSubReceived);
}

void BoardTransceiverNode::onPacketReceived(const QByteArray& packet)
{
    d->activeLine = qobject_cast<AbstractExchanger*>(this->sender());
    d->receiver->processPacket(packet);
}

void BoardTransceiverNode::onTimeout()
{
    d->activeLine = nullptr;
}

void BoardTransceiverNode::transmitPacket(const QByteArray& packet)
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
