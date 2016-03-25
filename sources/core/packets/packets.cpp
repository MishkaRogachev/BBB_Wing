#include "packets.h"

// Qt
#include <QByteArray>

using namespace domain;

QByteArray Packet::toByteArray()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << *this;
    return data;
}
