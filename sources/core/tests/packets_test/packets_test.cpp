#include "packets_test.h"

// Qt
#include <QDebug>

// Internal
#include "drive_impacts_packet.h"
#include "flight_point_packet.h"
#include "flight_program_packet.h"
#include "crc_packet.h"
#include "direct_packet.h"
#include "reverse_packet.h"

using namespace domain;

template<typename T>
T PacketsTest::testPacketSerialization(const T& packet)
{
    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << packet;
    }
    T converted;
    {
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream >> converted;
    }
    return converted;
}

void PacketsTest::testAltPacket()
{
    AltPacket packet;

    packet.status = true;

    packet.altitude = 3527.821;
    packet.temperature = -4.534;

    AltPacket converted = this->testPacketSerialization<AltPacket>(packet);

    QVERIFY(qFuzzyCompare(converted.altitude, packet.altitude));
    QVERIFY(qFuzzyCompare(converted.altitude, packet.altitude));
}

void PacketsTest::testInsPacket()
{
    InsPacket packet;

    packet.status = true;

    packet.pitch = -12.12;
    packet.roll = 58.33;
    packet.yaw = 34.55;

    InsPacket converted = this->testPacketSerialization<InsPacket>(packet);

    QVERIFY(qFuzzyCompare(converted.pitch, packet.pitch));
    QVERIFY(qFuzzyCompare(converted.roll, packet.roll));
    QVERIFY(qFuzzyCompare(converted.yaw, packet.yaw));
}

void PacketsTest::testSnsPacket()
{
    SnsPacket packet;

    packet.status = true;
    packet.fix = 3;

    packet.fix2d.latitude = 43.23474;
    packet.fix2d.longitude = 53.93562;
    packet.fix2d.groundSpeed = 15.68;
    packet.fix2d.yaw = 273.44;

    packet.fix3d.altitude = 2346.123;
    packet.fix3d.climb = -0.45;

    SnsPacket converted = this->testPacketSerialization<SnsPacket>(packet);

    QCOMPARE(converted.fix, packet.fix);

    QVERIFY(qFuzzyCompare(converted.fix2d.latitude, packet.fix2d.latitude));
    QVERIFY(qFuzzyCompare(converted.fix2d.longitude, packet.fix2d.longitude));
    QVERIFY(qFuzzyCompare(converted.fix2d.groundSpeed, packet.fix2d.groundSpeed));
    QVERIFY(qFuzzyCompare(converted.fix2d.yaw, packet.fix2d.yaw));

    QVERIFY(qFuzzyCompare(converted.fix3d.altitude, packet.fix3d.altitude));
    QVERIFY(qFuzzyCompare(converted.fix3d.climb, packet.fix3d.climb));
}

void PacketsTest::testDriveImpactsPacket()
{
    DriveImpactsPacket packet;

    packet.impacts = DriveImpacts { { 0,  56.45 },
                                    { 1, -73.01 } ,
                                    { 2, 223.42 } };

    DriveImpactsPacket converted =
            this->testPacketSerialization<DriveImpactsPacket>(packet);

    QCOMPARE(converted.impacts, packet.impacts);
}

void PacketsTest::testFlightPointPacket()
{
    FlightPointPacket packet;

    packet.latitude = 56.3275;
    packet.longitude = 32.163;
    packet.altitude = 1245.43;

    FlightPointPacket converted =
            this->testPacketSerialization<FlightPointPacket>(packet);

    QCOMPARE(converted.latitude, packet.latitude);
    QCOMPARE(converted.longitude, packet.longitude);
    QCOMPARE(converted.altitude, packet.altitude);
}

void PacketsTest::testFlightProgramPacket()
{
    FlightProgramPacket packet;

    packet.points.append(FlightPointPacket(48.4512, 34.2638, 2751.5));
    packet.points.append(FlightPointPacket(12.7241, 27.8436, 5244.3));

    FlightProgramPacket converted =
            this->testPacketSerialization<FlightProgramPacket>(packet);

    QCOMPARE(converted.points[0].latitude, packet.points[0].latitude);
    QCOMPARE(converted.points[0].longitude, packet.points[0].longitude);
    QCOMPARE(converted.points[0].altitude, packet.points[0].altitude);
    QCOMPARE(converted.points[1].latitude, packet.points[1].latitude);
    QCOMPARE(converted.points[1].longitude, packet.points[1].longitude);
    QCOMPARE(converted.points[1].altitude, packet.points[1].altitude);
}

void PacketsTest::testTransmissionPacket()
{
    CrcPacket packet("some_topic", "somedata123");

    CrcPacket converted = this->testPacketSerialization<CrcPacket>(packet);

    QCOMPARE(converted.topic, packet.topic);
    QCOMPARE(converted.data, packet.data);
    QVERIFY(converted.validateCrc());

    converted.data = "another_data";
    QVERIFY(!converted.validateCrc());
    converted.calcCrc();
    QVERIFY(converted.validateCrc());
}

void PacketsTest::testDirectPacket()
{
    {
        DirectPacket packet;

        packet.isManual = true;
        packet.manual.pitchControl = 143.41;
        packet.manual.rollControl = -23.03;
        packet.manual.courseControl = 137.123;
        packet.manual.speedControl = 46.324;

        DirectPacket converted = this->testPacketSerialization<DirectPacket>(packet);

        QCOMPARE(converted.isManual, packet.isManual);
        QCOMPARE(converted.manual.pitchControl, packet.manual.pitchControl);
        QCOMPARE(converted.manual.rollControl, packet.manual.rollControl);
        QCOMPARE(converted.manual.courseControl, packet.manual.courseControl);
        QCOMPARE(converted.manual.speedControl, packet.manual.speedControl);
    }

    {
        DirectPacket packet;

        packet.isManual = false;

        packet.automatic.isAltitudeOverridden = true;
        packet.automatic.overriddenAltitude = 60403;
        packet.automatic.isVelocityOverridden = true;
        packet.automatic.overriddenVelocity = 35;
        packet.automatic.isCourseOverridden = false;
        packet.automatic.activeProgram = 34525;
        packet.automatic.activePoint = 3;

        DirectPacket converted = this->testPacketSerialization<DirectPacket>(packet);

        QCOMPARE(converted.isManual, packet.isManual);
        QCOMPARE(converted.automatic.isAltitudeOverridden,
                 packet.automatic.isAltitudeOverridden);
        QCOMPARE(converted.automatic.overriddenAltitude,
                 packet.automatic.overriddenAltitude);
        QCOMPARE(converted.automatic.isVelocityOverridden,
                 packet.automatic.isVelocityOverridden);
        QCOMPARE(converted.automatic.overriddenVelocity,
                 packet.automatic.overriddenVelocity);
        QCOMPARE(converted.automatic.isCourseOverridden,
                 packet.automatic.isCourseOverridden);
        QCOMPARE(converted.automatic.activeProgram, packet.automatic.activeProgram);
        QCOMPARE(converted.automatic.activePoint, packet.automatic.activePoint);
    }
}

void PacketsTest::testReversePacket()
{
    ReversePacket packet;

    packet.altAvalible = true;
    packet.alt.status = true;
    packet.alt.altitude = 7195.76;
    packet.alt.altitude = -26.63;
    packet.insAvalible = true;
    packet.ins.status = false;
    packet.snsAvalible = false;

    ReversePacket converted =
            this->testPacketSerialization<ReversePacket>(packet);

    QCOMPARE(converted.altAvalible, packet.altAvalible);
    QCOMPARE(converted.alt.toByteArray(), packet.alt.toByteArray());
    QCOMPARE(converted.insAvalible, packet.insAvalible);
    QCOMPARE(converted.ins.toByteArray(), packet.ins.toByteArray());
    QCOMPARE(converted.snsAvalible, packet.snsAvalible);
}
