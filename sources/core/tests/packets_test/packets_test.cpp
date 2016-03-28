#include "packets_test.h"

// Qt
#include <QDebug>

// Internal
#include "alt_packet.h"
#include "ins_packet.h"
#include "sns_packet.h"
#include "transmission_packet.h"

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

    packet.altitude = 3527.821;
    packet.temperature = -4.534;

    AltPacket converted = this->testPacketSerialization<AltPacket>(packet);

    QVERIFY(qFuzzyCompare(converted.altitude, packet.altitude));
    QVERIFY(qFuzzyCompare(converted.altitude, packet.altitude));
}

void PacketsTest::testInsPacket()
{
    InsPacket packet;

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

    packet.fix = 2;

    packet.latitude = 43.23474;
    packet.longitude = 53.93562;
    packet.groundSpeed = 15.68;
    packet.yaw = 273.44;

    packet.altitude = 2346.123;
    packet.climb = -0.45;

    SnsPacket converted = this->testPacketSerialization<SnsPacket>(packet);

    QCOMPARE(converted.fix, packet.fix);

    QVERIFY(qFuzzyCompare(converted.latitude, packet.latitude));
    QVERIFY(qFuzzyCompare(converted.longitude, packet.longitude));
    QVERIFY(qFuzzyCompare(converted.groundSpeed, packet.groundSpeed));
    QVERIFY(qFuzzyCompare(converted.yaw, packet.yaw));

    QVERIFY(qFuzzyCompare(converted.altitude, packet.altitude));
    QVERIFY(qFuzzyCompare(converted.climb, packet.climb));
}

void PacketsTest::testTransmissionPacket()
{
    TransmissionPacket packet;

    packet.data = QByteArray("somedata123");
    packet.calcCrc();

    TransmissionPacket converted = this->testPacketSerialization<TransmissionPacket>(packet);

    QCOMPARE(converted.data, packet.data);
    QVERIFY(converted.crc);
}
