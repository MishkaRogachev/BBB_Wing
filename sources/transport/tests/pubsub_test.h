#ifndef ABSTRACT_AREA_TEST_H
#define ABSTRACT_AREA_TEST_H

#include <QtTest/QTest>

namespace domain
{
    class PubsubTest: public QObject
    {
        Q_OBJECT

    private slots:
        void oneToOne();
    };
}

#endif // ABSTRACT_AREA_TEST_H
