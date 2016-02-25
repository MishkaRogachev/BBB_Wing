// Qt
#include <QCoreApplication>

// Tests
#include "packets_test.h"
#include "pub_sub_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::PacketsTest packetsTest;
    QTest::qExec(&packetsTest);

    domain::PubsubTest pubsubTest;
    QTest::qExec(&pubsubTest);

    return 0;
}
