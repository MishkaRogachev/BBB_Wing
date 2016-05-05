#ifndef PACKETS_TEST_H
#define PACKETS_TEST_H

#include <QtTest/QTest>

namespace domain
{
    class Packet;

    class PacketsTest: public QObject
    {
        Q_OBJECT

    protected:
        template<typename T>
        T testPacketSerialization(const T& packet);

    private slots:
        void testAltPacket();
        void testInsPacket();
        void testSnsPacket();
        void testDriveImpactsPacket();
        void testFailuresPacket();
        void testTransmissionPacket();
        void testDirectPacket();
    };
}

#endif // PACKETS_TEST_H
