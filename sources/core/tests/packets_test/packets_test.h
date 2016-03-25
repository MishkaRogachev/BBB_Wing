#ifndef PACKETS_TEST_H
#define PACKETS_TEST_H

#include <QtTest/QTest>

namespace domain
{
    class PacketsTest: public QObject
    {
        Q_OBJECT

    private slots: // TODO: local packets
        void testBoardPacket();
        void testGroundPacketManual();
        void testGroundPacketAutomatic();
    };
}

#endif // PACKETS_TEST_H
