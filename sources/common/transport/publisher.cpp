#include "publisher.h"

// ZeroMQ
#include <zmq.hpp>

using namespace domain;

Publisher::Publisher(const QString& endpoint, QObject* parent):
    BaseTransport(ZMQ_PUB, parent)
{
    this->bind(endpoint);
}
