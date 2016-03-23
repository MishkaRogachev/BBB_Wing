#ifndef ABSTRACT_NAVIGATION_STATE_H
#define ABSTRACT_NAVIGATION_STATE_H

namespace domain
{
    class AbstractNavigationState
    {
    public:
        AbstractNavigationState();
        virtual ~AbstractNavigationState();

        virtual void process() = 0;
    };
}

#endif // ABSTRACT_NAVIGATION_STATE_H
