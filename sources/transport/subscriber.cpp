#include "subscriber.h"

// ZeroMQ
#include <zmq.hpp>

// Qt
#include <QSocketNotifier>

using namespace domain;

Subscriber::Subscriber(const QString& endpoint, QObject* parent):
    Subscriber(QStringList(endpoint), parent)
{}

Subscriber::Subscriber(const QStringList& endpoints, QObject* parent):
    BaseTransport(ZMQ_PUB, parent)
{
    for (const QString& endpoint: endpoints)
        this->connectTo(endpoint);

    QSocketNotifier* notifier = new QSocketNotifier(this->fileDescriptor(),
                                    QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated, this, &Subscriber::recv);
}

void Subscriber::subscribe(const QString& topic)
{
    this->setOption(ZMQ_SUBSCRIBE, topic);
}

void Subscriber::unsubscribe(const QString& topic)
{
    this->setOption(ZMQ_UNSUBSCRIBE, topic);
}

void Subscriber::recv()
{

}
