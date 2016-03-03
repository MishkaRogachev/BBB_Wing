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
        Q_PROPERTY(float velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)
        Q_PROPERTY(float altitude READ altitude WRITE setAltitude NOTIFY altitudeChanged)

    public:
        explicit BoardService(QObject* parent = nullptr);
        ~BoardService() override;

        float pitch() const;
        float roll() const;
        float yaw() const;
        float velocity() const;
        float altitude() const;

    public slots:
        void setPitch(float pitch);
        void setRoll(float roll);
        void setYaw(float yaw);
        void setVelocity(float velocity);
        void setAltitude(float altitude);

    signals:
        void pitchChanged(float pitch);
        void rollChanged(float roll);
        void yawChanged(float yaw);

        void velocityChanged(float velocity);

        void altitudeChanged(float altitude);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_SERVICE_H
