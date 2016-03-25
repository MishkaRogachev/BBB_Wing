#ifndef ABSTRACT_NAVIGATION_STATE_H
#define ABSTRACT_NAVIGATION_STATE_H

// Qt
#include <QObject>
#include <QScopedPointer>

// Internal
#include "sns_packet.h"
#include "ins_packet.h"

namespace domain
{
    class Publisher;

    struct NavigationStateData
    {
        SnsPacket sns;
        InsPacket ins;

        float altimeterAltitude = 0.0f;
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
