#include "packet.h"

// Qt
#include <QByteArray>

using namespace domain;

Packet::~Packet()
{}

QByteArray Packet::toByteArray() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << *this;
    return data;
}
