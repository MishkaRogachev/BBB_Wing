#include "board_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

#include "udp_transceiver.h"
#include "serial_port_transceiver.h"

#include "board_receiver_node.h"
#include "board_transmitter_node.h"

using namespace domain;

class BoardTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractTransceiver* wireTransceiver;
    AbstractTransceiver* airTransceiver;

    BoardReceiverNode* receiver;
    BoardTransmitterNode* transmitter;
};

BoardTransceiverNode::BoardTransceiverNode(QObject* parent):
    BranchNode(parent),
    d(new Impl())
{
    Config::begin("Transceiver");
    d->pub.bind("ipc://transceiver");

    d->wireTransceiver = new UdpTransceiver(
        QHostAddress(Config::setting("udp_board_address").toString()),
        Config::setting("udp_board_port").toInt(),
        QHostAddress(Config::setting("udp_workstation_address").toString()),
        Config::setting("udp_workstation_port").toInt(), this);
    connect(d->wireTransceiver, &AbstractTransceiver::received,
            this, &BoardTransceiverNode::onPacketReceived);

    d->airTransceiver = new SerialPortTransceiver(
        Config::setting("serial_port_board").toString(), this);
    connect(d->airTransceiver, &AbstractTransceiver::received,
            this, &BoardTransceiverNode::onPacketReceived);

    // 1 Hz for timeout
    d->receiver = new BoardReceiverNode(1, &d->pub);
    this->addNode(d->receiver);

    d->transmitter = new BoardTransmitterNode(10);
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
    d->receiver->onPacketReceived(packet);
}

void BoardTransceiverNode::transmitPacket(const QByteArray& packet)
{
    d->wireTransceiver->transmit(packet);
    d->airTransceiver->transmit(packet);
}
