#include "sensor_sns_node.h"

// Qt
#include <QDebug>

// Internal
#include "publisher.h"

using namespace domain;

class SensorSnsNode::Impl
{
public:
    Publisher pub;
};

SensorSnsNode::SensorSnsNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://sns"); //inproc://altimeter
    d->pub.setTopic("sns_");
}

SensorSnsNode::~SensorSnsNode()
{
    delete d;
}

void SensorSnsNode::init()
{}

void SensorSnsNode::exec()
{}
