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

        float frequency() const;

    public slots:
        void start() override;
        void stop() override;

        virtual void exec() = 0;

        void setFrequency(float frequency);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        int m_timerId;
        float m_frequency;
    };
}

#endif // ABSTRACT_NODE_FREQUENCY_H
