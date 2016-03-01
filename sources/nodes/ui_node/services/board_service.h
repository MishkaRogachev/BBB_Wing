#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

#include <QObject>

namespace domain
{
    class BoardService: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(float pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
        Q_PROPERTY(float roll READ roll WRITE setRoll NOTIFY rollChanged)
        Q_PROPERTY(float yaw READ yaw WRITE setYaw NOTIFY yawChanged)

    public:
        explicit BoardService(QObject* parent = nullptr);
        ~BoardService() override;

        float pitch() const;
        float roll() const;
        float yaw() const;

    public slots:
        void setPitch(float pitch);
        void setRoll(float roll);
        void setYaw(float yaw);

    signals:
        void pitchChanged(float pitch);
        void rollChanged(float roll);
        void yawChanged(float yaw);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_SERVICE_H
