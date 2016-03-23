#ifndef ABSTRACT_NAVIGATION_STATE_H
#define ABSTRACT_NAVIGATION_STATE_H

// Qt
#include <QString>

namespace domain
{
    class Publisher;

    class AbstractNavigationState
    {
    public:
        AbstractNavigationState(Publisher* pub);
        virtual ~AbstractNavigationState();

        virtual QString stateId() const = 0;
        virtual void process();

    protected:
        Publisher* m_pub;
    };
}

#endif // ABSTRACT_NAVIGATION_STATE_H
