#include "packet.h"

// Qt
#include <QByteArray>

using namespace domain;

QByteArray Packet::toByteArray() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << *this;
    return data;
}
