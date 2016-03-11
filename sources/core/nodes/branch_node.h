#ifndef BRANCH_NODE_H
#define BRANCH_NODE_H

#include "abstract_node.h"

namespace domain
{
    class BranchNode: public AbstractNode
    {
        Q_OBJECT

    public:
        BranchNode(QObject* parent = nullptr);

        const QList<AbstractNode*>& nodes() const;

    public slots:
        void init() override;
        void start() override;
        void stop() override;

        void addNode(AbstractNode* node);
        void removeNode(AbstractNode* node);

    private:
        QList<AbstractNode*> m_nodes;
    };
}

#endif // BRANCH_NODE_H
