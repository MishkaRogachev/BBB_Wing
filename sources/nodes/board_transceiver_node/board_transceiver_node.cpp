#include "board_transceiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class BoardTransceiverNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

BoardTransceiverNode::BoardTransceiverNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://transceiver");
    d->pub.setTopic("tr_");
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
     connect(&d->sub, &Subscriber::received, this, &BoardTransceiverNode::onReceived);
}

void BoardTransceiverNode::exec()
{

}

void BoardTransceiverNode::onReceived(const QString& topic, const QByteArray& msg)
{

}
