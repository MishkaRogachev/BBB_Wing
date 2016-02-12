#ifndef ABSTRACT_NODE_FREQUENCY_H
#define ABSTRACT_NODE_FREQUENCY_H

#include "abstract_node.h"

namespace domain
{
    class AbstractNodeFrequency: public AbstractNode
    {
        Q_OBJECT

    public:
        AbstractNodeFrequency(QObject* parent = nullptr);

    public slots:
        void start(float frequency);
        void stop();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        int m_timerId;
    };
}

#endif // ABSTRACT_NODE_FREQUENCY_H
