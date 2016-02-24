#include "base_transport.h"

// ZeroMQ
#include <zmq.hpp>

using namespace domain;

class BaseTransport::Impl
{
public:
    static zmq::context_t context;
    zmq::socket_t socket;

    Impl(int type):
        socket(context, type)
    {}
};

zmq::context_t BaseTransport::Impl::context(1);

BaseTransport::BaseTransport(int type, QObject* parent):
    QObject(parent),
    d(new Impl(type))
{}

BaseTransport::~BaseTransport()
{
    d->socket.close();
    delete d;
}

void BaseTransport::connectTo(const QString& endpoint)
{
    d->socket.connect(endpoint.toStdString().c_str());
}

void BaseTransport::bind(const QString& endpoint)
{
    d->socket.bind(endpoint.toStdString().c_str());
}

void BaseTransport::setOption(int option, const QString& value)
{
    auto stdString = value.toStdString();
    d->socket.setsockopt(option, stdString.c_str(), stdString.length());
}

qint32 BaseTransport::fileDescriptor() const
{
    qint32 fd;
    size_t size = sizeof(fd);
    d->socket.getsockopt(ZMQ_FD, &fd, &size);
    return fd;
}

QByteArray BaseTransport::recv(int flags)
{
    zmq::message_t message;
    d->socket.recv(&message, flags);

    return QByteArray(static_cast<char*>(message.data()), message.size());
}

void BaseTransport::send(const QByteArray& data, int flags)
{
     zmq::message_t message(data.size());
     memcpy(message.data(), data.data(), data.size());

     d->socket.send(message, flags);
}
