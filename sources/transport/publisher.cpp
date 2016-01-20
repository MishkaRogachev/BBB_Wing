#include "publisher.h"

// ZeroMQ
#include <zmq.hpp>

using namespace domain;

Publisher::Publisher(const QString& endpoint, QObject* parent):
    BaseTransport(ZMQ_PUB, parent)
{
    this->bind(endpoint);
}

void Publisher::publish(const QString& topic, const QByteArray& data)
{
    this->send(topic.toLatin1(), ZMQ_SNDMORE);
    this->send(data);
}
