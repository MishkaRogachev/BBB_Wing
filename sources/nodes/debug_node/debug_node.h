#ifndef DEBUG_NODE_H
#define DEBUG_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class DebugNode: public AbstractNodeFrequency
    {
    public:
        DebugNode(QObject* parent = nullptr);
        ~DebugNode() override;

        void init() override;
        void exec() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // DEBUG_NODE_H
