#ifndef ABSTRACT_NAVIGATION_STATE_H
#define ABSTRACT_NAVIGATION_STATE_H

#include <QObject>
#include <QScopedPointer>

namespace domain
{
    class Publisher;

    struct NavigationStateData
    {
        float latitude = 0.0f;
        float longitude = 0.0f;

        float altimeterAltitude = 0.0f;
        float snsAltitude = 0.0f;

        float velocity = 0.0f;
        float climb = 0.0f;

        float pitch = 0.0f;
        float roll = 0.0f;
        float yaw = 0.0;
    };

    class AbstractNavigationState: public QObject
    {
        Q_OBJECT

    public:
        AbstractNavigationState(NavigationStateData* data,
                                QObject* parent = nullptr);
        virtual ~AbstractNavigationState();

        virtual QString stateId() const = 0;

        friend class TakeoffNavigationState;

    public slots:
        virtual void onSubReceived(const QString& topic, const QByteArray& msg);

        virtual void process();

    signals:
        void publish(const QString& topic, const QByteArray& msg);
        void requestNewState(AbstractNavigationState* state);

    protected:
        QScopedPointer<NavigationStateData> m_data;
    };
}

#endif // ABSTRACT_NAVIGATION_STATE_H
