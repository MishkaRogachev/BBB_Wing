#include "ground_gateway_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class GroundGatewayNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

GroundGatewayNode::GroundGatewayNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://ground_gateway");
}

GroundGatewayNode::~GroundGatewayNode()
{
    delete d;
}

void GroundGatewayNode::init()
{
     d->sub.connectTo("ipc://alt");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://navigator");
     d->sub.connectTo("ipc://controller");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this,
             &GroundGatewayNode::onSubReceived);
}

void GroundGatewayNode::exec()
{

}

void GroundGatewayNode::onSubReceived(const QString& topic, const QByteArray& msg)
{

}

void GroundGatewayNode::onLineReceived(const QByteArray& packet)
{

}
