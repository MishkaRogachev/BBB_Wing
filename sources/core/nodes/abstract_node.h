#ifndef ABSTRACT_NODE_H
#define ABSTRACT_NODE_H

#include <QObject>

namespace domain
{
    class AbstractNode: public QObject
    {
        Q_OBJECT

    public:
        AbstractNode(QObject* parent = nullptr);
        virtual ~AbstractNode();

    public slots:
        virtual void init();
        virtual void exec() = 0;
    };
}

#endif // ABSTRACT_NODE_H
