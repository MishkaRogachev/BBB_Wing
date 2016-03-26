#include "board_service.h"

// Qt
#include <QDebug>

using namespace domain;

BoardService::BoardService(QObject* parent):
    QObject(parent),
    m_snsFix(0),
    m_position(),
    m_groundSpeed(0),
    m_climb(0),
    m_snsAltitude(0),
    m_yaw(0)
{}

int BoardService::snsFix() const
{
    return m_snsFix;
}

QGeoCoordinate BoardService::position() const
{
    return m_position;
}

float BoardService::groundSpeed() const
{
    return m_groundSpeed;
}

float BoardService::climb() const
{
    return m_climb;
}

float BoardService::snsAltitude() const
{
    return m_snsAltitude;
}

float BoardService::pitch() const
{
    return m_pitch;
}

float BoardService::roll() const
{
    return m_roll;
}

float BoardService::yaw() const
{
    return m_yaw;
}

float BoardService::barAltitude() const
{
    return m_barAltitude;
}

float BoardService::temperature() const
{
    return m_temperature;
}

void BoardService::updateSnsData(const SnsPacket& packet)
{
    if (m_snsFix != packet.fix)
    {
        m_snsFix = packet.fix;
        emit snsFixChanged(packet.fix);
    }

    QGeoCoordinate position = packet.fix > 1 ? QGeoCoordinate(packet.latitude,
                                           packet.longitude, packet.altitude) :
                                           QGeoCoordinate();
    if (m_position != position)
    {
        m_position = position;
        emit positionChanged(position);
    }

    if (!qFuzzyCompare(m_groundSpeed, packet.groundSpeed))
    {
        m_groundSpeed = packet.groundSpeed;
        emit groundSpeedChanged(packet.groundSpeed);
    }

    if (!qFuzzyCompare(m_climb, packet.climb))
    {
        m_climb = packet.climb;
        emit climbChanged(packet.climb);
    }

    if (!qFuzzyCompare(m_snsAltitude, packet.altitude))
    {
        m_snsAltitude = packet.altitude;
        emit groundSpeedChanged(packet.altitude);
    }
}

void BoardService::updateInsData(const InsPacket& packet)
{
    if (!qFuzzyCompare(m_pitch, packet.pitch))
    {
        m_pitch = packet.pitch;
        emit pitchChanged(packet.pitch);
    }

    if (!qFuzzyCompare(m_roll, packet.roll))
    {
        m_roll = packet.roll;
        emit rollChanged(packet.roll);
    }

    if (!qFuzzyCompare(m_yaw, packet.yaw))
    {
        m_yaw = packet.yaw;
        emit yawChanged(packet.yaw);
    }
}

void BoardService::updateAltData(const AltPacket& packet)
{
    if (!qFuzzyCompare(m_barAltitude, packet.altitude))
    {
        m_barAltitude = packet.altitude;
        emit barAltitudeChanged(packet.altitude);
    }

    if (!qFuzzyCompare(m_temperature, packet.temperature))
    {
        m_temperature = packet.temperature;
        emit temperatureChanged(packet.temperature);
    }
}
