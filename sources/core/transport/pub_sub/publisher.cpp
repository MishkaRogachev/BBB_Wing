#include "publisher.h"

// ZeroMQ
#include <zmq.hpp>

using namespace domain;

Publisher::Publisher(QObject* parent):
    PubSubBase(ZMQ_PUB, parent)
{}

Publisher::Publisher(const QString& endpoint, QObject* parent):
    Publisher(parent)
{
    this->bind(endpoint);
}

Publisher::Publisher(const QString& endpoint, const QString& topic,
                     QObject* parent):
    Publisher(endpoint, parent)
{
    m_topic = topic;
}

QString Publisher::topic() const
{
    return m_topic;
}

void Publisher::setTopic(const QString& topic)
{
    m_topic = topic;
}

void Publisher::publish(const QByteArray& data)
{
    this->publish(QString(), data);
}

void Publisher::publish(const QString& topic, const QByteArray& data)
{
    this->send((m_topic + topic).toLatin1(), ZMQ_SNDMORE);
    this->send(data);
}
