#include "packets_test.h"

// Internal
#include "board_packet.h"

using namespace domain;

void PacketsTest::testBasePacket()
{
    BasePacket packet;

    packet.type = PacketType::Base;
    packet.crc = 666;

    QByteArray data;
    QDataStream stream(data);

    stream << packet;
    BasePacket converted;
    stream >> converted;

    QCOMPARE(packet.type, converted.type);
    QCOMPARE(packet.crc, converted.crc);
}

void PacketsTest::testBoardPacket()
{

}
