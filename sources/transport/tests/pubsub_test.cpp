#include "pubsub_test.h"

// Qt
#include <QtTest/QSignalSpy>

// Internal
#include "publisher.h"
#include "subscriber.h"

using namespace domain;

void PubsubTest::oneToOne()
{
    Publisher pub("inproc://test");

    Subscriber sub("inproc://test");
    QSignalSpy spy(&sub, &Subscriber::received);

}
