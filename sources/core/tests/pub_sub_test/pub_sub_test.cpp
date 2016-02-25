#include "pub_sub_test.h"

// Internal
#include "publisher.h"
#include "subscriber.h"

using namespace domain;

void PubsubTest::oneToOne()
{
    QString topic = "test_topic";
    QList<QByteArray> msgs = { "first_msg", "another_msg", "last_msg" };

    Publisher pub("inproc://test", topic);
    Subscriber sub("inproc://test", topic);

    for (const QByteArray& msg: msgs)
    {
        pub.publish(msg);
        QCOMPARE(QString(sub.recv()), topic);
        QCOMPARE(sub.recv(), msg);
    }
}

void PubsubTest::topicFiltring()
{
    Publisher pub("inproc://test2");
    Subscriber sub("inproc://test2");

    pub.publish("abc", "test");

    QCOMPARE(sub.recv(1), QByteArray());

    sub.subscribe("abc");
    pub.publish("abc", "test");

    QCOMPARE(sub.recv(1), QByteArray("abc"));
    QCOMPARE(sub.recv(1), QByteArray("test"));

    pub.publish("abc123", "test2");

    QCOMPARE(sub.recv(1), QByteArray("abc123"));
    QCOMPARE(sub.recv(1), QByteArray("test2"));

    sub.unsubscribe("abc");
    pub.publish("abc123", "test3");

    QCOMPARE(sub.recv(1), QByteArray());
}

void PubsubTest::oneToMany()
{
    Publisher pub("inproc://test3", "test");
    Subscriber sub1("inproc://test3", "test");
    Subscriber sub2("inproc://test3", "test");

    pub.publish("123");

    QCOMPARE(sub1.recv(1), QByteArray("test"));
    QCOMPARE(sub1.recv(1), QByteArray("123"));
    QCOMPARE(sub2.recv(1), QByteArray("test"));
    QCOMPARE(sub2.recv(1), QByteArray("123"));

    sub2.unsubscribe("test");
    pub.publish("abc");

    QCOMPARE(sub1.recv(1), QByteArray("test"));
    QCOMPARE(sub1.recv(1), QByteArray("abc"));
    QCOMPARE(sub2.recv(1), QByteArray());
}

void PubsubTest::manyToOne()
{
    Publisher pub1("inproc://test41");
    Publisher pub2("inproc://test42");
    Subscriber sub;
    sub.connectTo("inproc://test41");
    sub.connectTo("inproc://test42");
    sub.subscribe("test");

    pub1.publish("test", "123");
    QCOMPARE(sub.recv(1), QByteArray("test"));
    QCOMPARE(sub.recv(1), QByteArray("123"));

    pub2.publish("test", "abc");
    QCOMPARE(sub.recv(1), QByteArray("test"));
    QCOMPARE(sub.recv(1), QByteArray("abc"));

    sub.subscribe("pub1");
    sub.subscribe("pub2");

    pub1.publish("pub1", "123");
    QCOMPARE(sub.recv(1), QByteArray("pub1"));
    QCOMPARE(sub.recv(1), QByteArray("123"));

    pub2.publish("pub2", "abc");
    QCOMPARE(sub.recv(1), QByteArray("pub2"));
    QCOMPARE(sub.recv(1), QByteArray("abc"));

}
