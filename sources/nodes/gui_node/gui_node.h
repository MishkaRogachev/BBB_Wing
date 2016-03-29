#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "abstract_node.h"

namespace domain
{
    class GuiNode: public AbstractNode
    {
        Q_OBJECT

    public:
        GuiNode(QObject* parent = nullptr);
        ~GuiNode() override;

    public slots:
        void init() override;
        void start() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // GUI_NODE_H
