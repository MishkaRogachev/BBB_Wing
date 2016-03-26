#include "board_gateway_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class BoardGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

BoardGatewayNode::BoardGatewayNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://board_gateway");
}

BoardGatewayNode::~BoardGatewayNode()
{
    delete d;
}

void BoardGatewayNode::init()
{
     d->sub.connectTo("ipc://alt");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://navigator");
     d->sub.connectTo("ipc://controller");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this,
             &BoardGatewayNode::onSubReceived);
}

void BoardGatewayNode::exec()
{

}

void BoardGatewayNode::onSubReceived(const QString& topic, const QByteArray& msg)
{

}

void BoardGatewayNode::onLineReceived(const QByteArray& packet)
{

}
