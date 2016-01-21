// Qt
#include <QCoreApplication>

// Tests
#include "pubsub_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::PubsubTest pubsubTest;
    QTest::qExec(&pubsubTest);

    return 0;
}
