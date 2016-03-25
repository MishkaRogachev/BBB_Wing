#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

// Qt
#include <QObject>
#include <QtPositioning/QGeoCoordinate>

// Internal
#include "sns_packet.h"
#include "ins_packet.h"
#include "alt_packet.h"

namespace domain
{
    class BoardService: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QGeoCoordinate position READ position NOTIFY positionChanged)
        Q_PROPERTY(float velocity READ velocity NOTIFY velocityChanged)
        Q_PROPERTY(float climb READ climb NOTIFY climbChanged)
        Q_PROPERTY(float snsAltitude READ snsAltitude NOTIFY snsAltitudeChanged)

        Q_PROPERTY(float pitch READ pitch NOTIFY pitchChanged)
        Q_PROPERTY(float roll READ roll NOTIFY rollChanged)
        Q_PROPERTY(float yaw READ yaw NOTIFY yawChanged)

        Q_PROPERTY(float barAltitude READ barAltitude NOTIFY barAltitudeChanged)
        Q_PROPERTY(float temperature READ temperature NOTIFY temperatureChanged)

    public:
        explicit BoardService(QObject* parent = nullptr);

        QGeoCoordinate position() const;
        float velocity() const;
        float climb() const;
        float snsAltitude() const;

        float pitch() const;
        float roll() const;
        float yaw() const;

        float barAltitude() const;
        float temperature() const;

    public slots:
        void updateSnsData(const SnsPacket& packet);
        void updateInsData(const InsPacket& packet);
        void updateAltData(const AltPacket& packet);

    signals:
        void positionChanged(QGeoCoordinate position);
        void velocityChanged(float velocity);
        void climbChanged(float climb);
        void snsAltitudeChanged(float snsAltitude);

        void pitchChanged(float pitch);
        void rollChanged(float roll);
        void yawChanged(float yaw);

        void barAltitudeChanged(float barAltitude);
        void temperatureChanged(float temperature);

    private:
        QGeoCoordinate m_position;
        float m_velocity;
        float m_climb;
        float m_snsAltitude;

        float m_pitch;
        float m_roll;
        float m_yaw;

        float m_barAltitude;
        float m_temperature;
    };
}

#endif // BOARD_SERVICE_H
