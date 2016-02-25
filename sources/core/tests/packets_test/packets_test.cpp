#include "packets_test.h"

// Qt
#include <QDebug>

// Internal
#include "board_packet.h"

using namespace domain;

void PacketsTest::testBoardPacket()
{
    BoardPacket packet;

    packet.data.latitude = 44.564133;
    packet.data.longitude = 35.31455;
    packet.data.altitude = 5679.435;

    packet.data.velocity = 56.0034;
    packet.data.climb = -4.324;

    packet.data.pitch = 5.4556;
    packet.data.roll = -11.567;
    packet.data.yaw = 356.645;

    packet.data.temperature = -4.987;

    packet.data.altimeterStatus = true;
    packet.data.insStatus = true;
    packet.data.snsStatus = false;

    packet.calcCrc();

    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << packet;
    BoardPacket converted;

    qDebug() << data;

    stream << converted;

    qDebug() << data;

    QCOMPARE(converted.data.latitude, 44.564133);
    QCOMPARE(converted.data.velocity, 56.0034);
    QCOMPARE(converted.data.roll, -11.567);

    QCOMPARE(packet.crc, converted.crc);
    QVERIFY(converted.validateCrc());

    converted.data.altitude = 2334.456;

    QVERIFY(!converted.validateCrc());
    converted.calcCrc();
    QVERIFY(converted.validateCrc());
}
