#include "pubsub_test.h"

int main()
{
    domain::PubsubTest pubsubTest;
    QTest::qExec(&pubsubTest);

    return 0;
}

 
