#include "pubsub_test.h"

// Qt
#include <QtTest/QSignalSpy>

// Internal
#include "publisher.h"
#include "subscriber.h"

using namespace domain;

void PubsubTest::oneToOne()
{
    Publisher pub("tcp://*:5563");

    Subscriber sub("tcp://localhost:5563");
    sub.subscribe("test_topic");

    QSignalSpy spy(&sub, &Subscriber::received);
    QCOMPARE(spy.count(), 0);

    pub.publish("test_topic", "ping");

    QCOMPARE(spy.count(), 1);

    pub.publish("test_topic", "ping two");
}
