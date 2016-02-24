// Qt
#include <QCoreApplication>

// Tests
#include "packets_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::PacketsTest packetsTest;
    QTest::qExec(&packetsTest);

    return 0;
}
