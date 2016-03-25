#include "packets_test.h"

// Qt
#include <QDebug>

// Internal
#include "board_packet.h"
#include "ground_packet.h"

using namespace domain;

void PacketsTest::testBoardPacket()
{
    BoardPacket packet;
/*
    packet.data.latitude = 44.564;
    packet.data.longitude = 35.314;
    packet.data.altimeterAltitude = 5679.435;

    packet.data.velocity = 56.034;
    packet.data.climb = -4.324;

    packet.data.pitch = 5.455;
    packet.data.roll = -11.567;
    packet.data.yaw = 356.645;*/

    packet.data.temperature = -4.987;

    packet.data.altimeterStatus = true;
    packet.data.insStatus = true;
    packet.data.snsStatus = false;

    packet.calcCrc();

    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << packet;
    }
    BoardPacket converted;
    {
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream >> converted;
    }

    //QVERIFY(qFuzzyCompare(converted.data.latitude, packet.data.latitude));
    //QCOMPARE(converted.data.velocity, packet.data.velocity);
    //QCOMPARE(converted.data.roll, packet.data.roll);

    QCOMPARE(packet.crc, converted.crc);
    QVERIFY(converted.validateCrc());

    converted.data.altimeterAltitude = 2334.456;

    QVERIFY(!converted.validateCrc());
    converted.calcCrc();
    QVERIFY(converted.validateCrc());
}

void PacketsTest::testGroundPacketManual()
{
    GroundPacket packet;

    packet.data.isManual = true;

    packet.data.manual.setPitch = 3.23;
    packet.data.manual.setRoll = -36.12;
    packet.data.manual.setThrottle = 75;

    packet.calcCrc();

    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << packet;
    }
    GroundPacket converted;
    {
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream >> converted;
    }

    QCOMPARE(converted.data.isManual, packet.data.isManual);
    QVERIFY(qFuzzyCompare(converted.data.manual.setPitch, packet.data.manual.setPitch));
    QVERIFY(qFuzzyCompare(converted.data.manual.setRoll, packet.data.manual.setRoll));
    QCOMPARE(converted.data.manual.setThrottle, packet.data.manual.setThrottle);

    QCOMPARE(packet.crc, converted.crc);
    QVERIFY(converted.validateCrc());
}

void PacketsTest::testGroundPacketAutomatic()
{
    GroundPacket packet;

    packet.data.isManual = false;

    packet.data.automatic.activePoint = 3;
    packet.data.automatic.activeProgram = 1344;

    packet.data.automatic.isAltitudeOverriden = false;
    packet.data.automatic.isVelocityOverriden = true;
    packet.data.automatic.isYawOverriden = true;
    packet.data.automatic.overridenAltitude = -1;
    packet.data.automatic.overridenVelocity = 57;
    packet.data.automatic.overridenYaw = 234.23;

    packet.calcCrc();

    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << packet;
    }
    GroundPacket converted;
    {
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream >> converted;
    }

    QCOMPARE(converted.data.isManual, packet.data.isManual);

    QCOMPARE(converted.data.automatic.activePoint, packet.data.automatic.activePoint);
    QCOMPARE(converted.data.automatic.activeProgram, packet.data.automatic.activeProgram);

    QCOMPARE(converted.data.automatic.isAltitudeOverriden, packet.data.automatic.isAltitudeOverriden);
    QCOMPARE(converted.data.automatic.isVelocityOverriden, packet.data.automatic.isVelocityOverriden);
    QCOMPARE(converted.data.automatic.isYawOverriden, packet.data.automatic.isYawOverriden);
    QVERIFY(qFuzzyCompare(converted.data.automatic.overridenAltitude, packet.data.automatic.overridenAltitude));
    QVERIFY(qFuzzyCompare(converted.data.automatic.overridenVelocity, packet.data.automatic.overridenVelocity));
    QVERIFY(qFuzzyCompare(converted.data.automatic.overridenYaw, packet.data.automatic.overridenYaw));

    QCOMPARE(packet.crc, converted.crc);
    QVERIFY(converted.validateCrc());
}
