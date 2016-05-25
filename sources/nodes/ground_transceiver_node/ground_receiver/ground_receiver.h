#ifndef GROUND_RECEIVER_H
#define GROUND_RECEIVER_H

#include <QObject>

namespace domain
{
    class GroundReceiver: public QObject
    {
        Q_OBJECT

    public:
        explicit GroundReceiver(QObject* parent = nullptr);

    public slots:
        void onLinkReceived(const QByteArray& data);

    signals:
        void publish(const QString& topic, const QByteArray& data);
    };
}

#endif // GROUND_RECEIVER_H
