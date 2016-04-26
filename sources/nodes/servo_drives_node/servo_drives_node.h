#ifndef SERVO_DRIVES_NODE_H
#define SERVO_DRIVES_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class ServoDrivesNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        ServoDrivesNode(QObject* parent = nullptr);
        ~ServoDrivesNode() override;

    public slots:
        void init() override;
        void exec() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& msg);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SERVO_DRIVES_NODE_H
