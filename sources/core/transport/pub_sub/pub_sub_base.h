#ifndef PUB_SUB_BASE_H
#define PUB_SUB_BASE_H

#include <QObject>

namespace domain
{
    class PubSubBase: public QObject
    {
        Q_OBJECT

    public:
        PubSubBase(int type, QObject* parent = nullptr);
        ~PubSubBase() override;

        void connectTo(const QString& endpoint);
        void bind(const QString& endpoint);
        void unbind();

        void setOption(int option, const QString& value);

        QByteArray recv(int flags = 0);
        void send(const QByteArray& data, int flags = 0);

    protected:
        qint32 fileDescriptor() const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // PUB_SUB_BASE_H
