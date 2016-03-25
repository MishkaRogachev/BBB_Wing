#include "packets.h"

// Qt
#include <QByteArray>

using namespace domain;

QByteArray Packet::toByteArray()
{
    QByteArray data;
    QDataStream stream(data);
    stream << *this;
    return data;
}
