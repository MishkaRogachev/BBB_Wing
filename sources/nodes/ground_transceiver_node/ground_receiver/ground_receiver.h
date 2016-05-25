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

        int count() const;
        int packetsLost() const;

    public slots:
        void onLinkReceived(const QByteArray& data);
        void reset();

    signals:
        void publish(const QString& topic, const QByteArray& data);

    private:
        int m_count = 0;
        int m_packetsLost = 0;
    };
}

#endif // GROUND_RECEIVER_H
