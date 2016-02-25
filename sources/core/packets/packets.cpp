#include "packets.h"

using namespace domain;

quint16 DataPacket::calcCrc() const
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << *this;
    return qChecksum(array.data(), array.length());
}
