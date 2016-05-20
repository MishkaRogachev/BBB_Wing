#include "board_service.h"

// Qt
#include <QDebug>

//Internal
#include "core.h"

using namespace domain;

BoardService::BoardService(QObject* parent):
    QObject(parent),
    m_barAltitude(0),
    m_temperature(0),
    m_pitch(0),
    m_roll(0),
    m_yaw(0),
    m_snsFix(0),
    m_position(QGeoCoordinate()),
    m_snsYaw(0),
    m_groundSpeed(0),
    m_climb(0),
    m_snsAltitude(0),
    m_altStatus(false),
    m_insStatus(false),
    m_snsStatus(false)
{}

float BoardService::barAltitude() const
{
    return m_barAltitude;
}

float BoardService::temperature() const
{
    return m_temperature;
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

int BoardService::snsFix() const
{
    return m_snsFix;
}

QGeoCoordinate BoardService::position() const
{
    return m_position;
}

float BoardService::snsYaw() const
{
    return m_snsYaw;
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

bool BoardService::altStatus() const
{
    return m_altStatus;
}
// Internal
#include "direct_packet.h"
bool BoardService::insStatus() const
{
    return m_insStatus;
}

bool BoardService::snsStatus() const
{
    return m_snsStatus;
}

void BoardService::updateAltData(const AltPacket& packet)
{
    if (m_altStatus != packet.status)
    {
        m_altStatus = packet.status;
        emit altStatusChanged(m_altStatus);
    }

    if (!packet.status) return;

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

void BoardService::updateInsData(const InsPacket& packet)
{
    if (m_insStatus != packet.status)
    {
        m_insStatus = packet.status;
        emit insStatusChanged(m_insStatus);
    }

    if (!packet.status) return;

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

void BoardService::updateSnsData(const SnsPacket& packet)
{
    if (m_snsStatus != packet.status)
    {
        m_snsStatus = packet.status;
        emit snsStatusChanged(m_snsStatus);
    }

    if (!packet.status) return;

    if (m_snsFix != packet.fix)
    {
        m_snsFix = packet.fix;
        emit snsFixChanged(packet.fix);
    }

    QGeoCoordinate position;

    if (packet.fix > 1)
    {
        position.setLatitude(packet.fix2d.latitude);
        position.setLongitude(packet.fix2d.longitude);

        if (!qFuzzyCompare(m_snsYaw, packet.fix2d.yaw))
        {
            m_snsYaw = packet.fix2d.yaw;
            emit snsYawChanged(packet.fix2d.yaw);
        }

        if (!qFuzzyCompare(m_groundSpeed, packet.fix2d.groundSpeed))
        {
            m_groundSpeed = packet.fix2d.groundSpeed;
            emit groundSpeedChanged(packet.fix2d.groundSpeed);
        }

        if (packet.fix > 2)
        {
            position.setLongitude(packet.fix3d.altitude);

            if (!qFuzzyCompare(m_climb, packet.fix3d.climb))
            {
                m_climb = packet.fix3d.climb;
                emit climbChanged(packet.fix3d.climb);
            }

            if (!qFuzzyCompare(m_snsAltitude, packet.fix3d.altitude))
            {
                m_snsAltitude = packet.fix3d.altitude;
                emit snsAltitudeChanged(packet.fix3d.altitude);
            }
        }
    }

    if (m_position != position)
    {
        m_position = position;
        emit positionChanged(position);
    }
}

