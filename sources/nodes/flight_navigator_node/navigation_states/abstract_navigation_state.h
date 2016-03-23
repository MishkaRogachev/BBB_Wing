#ifndef ABSTRACT_NAVIGATION_STATE_H
#define ABSTRACT_NAVIGATION_STATE_H

#include <QObject>

namespace domain
{
    class Publisher;

    class AbstractNavigationState: public QObject
    {
        Q_OBJECT

    public:
        AbstractNavigationState(QObject* parent = nullptr);
        virtual ~AbstractNavigationState();

        virtual QString stateId() const = 0;

    public slots:
        virtual void onSubReceived(const QString& topic, const QByteArray& msg);

        virtual void process();

    signals:
        void publish(const QString& topic, const QByteArray& msg);
        void requestNewState(AbstractNavigationState* state);
    };
}

#endif // ABSTRACT_NAVIGATION_STATE_H
