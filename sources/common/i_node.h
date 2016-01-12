#ifndef I_NODE_H
#define I_NODE_H

namespace domain
{
    class INode
    {
    public:
        INode() {}
        virtual ~INode() {}

        virtual int exec() = 0;
    };
}

#endif // I_NODE_H
