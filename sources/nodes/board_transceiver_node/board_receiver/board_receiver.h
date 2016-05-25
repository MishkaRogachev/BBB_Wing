#ifndef BOARD_RECEIVER_H
#define BOARD_RECEIVER_H

#include <QObject>

namespace domain
{
    class BoardReceiver: public QObject
    {
        Q_OBJECT

    public:
        explicit BoardReceiver(QObject* parent = nullptr);

    public slots:
        void onLinkReceived(const QByteArray& data);

    signals:
        void publish(const QString& topic, const QByteArray& data);
    };
}

#endif // BOARD_RECEIVER_H
