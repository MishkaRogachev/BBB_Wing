#ifndef UI_NODE_H
#define UI_NODE_H

#include "abstract_node.h"

namespace domain
{
    class UiNode: public AbstractNode
    {
    public:
        UiNode(QObject* parent = nullptr);
        ~UiNode() override;

        void init() override;
        void exec() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // UI_NODE_H