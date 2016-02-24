#ifndef BASE_TRANSPORT_H
#define BASE_TRANSPORT_H

#include <QObject>
// TODO: move transport to core(common)

namespace domain
{
    class BaseTransport: public QObject
    {
        Q_OBJECT

    public:
        BaseTransport(int type, QObject* parent = nullptr);
        ~BaseTransport() override;

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

#endif // BASE_TRANSPORT_H
