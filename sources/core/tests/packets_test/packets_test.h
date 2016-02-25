#ifndef PACKETS_TEST_H
#define PACKETS_TEST_H

#include <QtTest/QTest>

namespace domain
{
    class PacketsTest: public QObject
    {
        Q_OBJECT

    private slots:
        void testBoardPacket();
    };
}

#endif // PACKETS_TEST_H
