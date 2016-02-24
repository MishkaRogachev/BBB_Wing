#include "packets_test.h"

// Qt
#include <QDebug>

// Internal
#include "board_packet.h"

using namespace domain;

void PacketsTest::testBasePacket()
{
    BasePacket packet;

    packet.crc = 666;

    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream >> packet;
    BasePacket converted;
    stream << converted;

    QCOMPARE(packet.type, converted.type);
    QCOMPARE(packet.crc, converted.crc);
}

void PacketsTest::testBoardPacket()
{

}
