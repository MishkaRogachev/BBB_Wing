#ifndef PUB_SUB_TEST_H
#define PUB_SUB_TEST_H

#include <QtTest/QTest>

namespace domain
{
    class PubsubTest: public QObject
    {
        Q_OBJECT

    private slots:
        void oneToOne();
        void topicFiltring();
        void oneToMany();
        void manyToOne();
    };
}

#endif // PUB_SUB_TEST_H
