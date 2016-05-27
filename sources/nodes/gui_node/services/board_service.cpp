#include "board_service.h"

// Qt
#include <QDebug>

//Internal
#include "core.h"
#include "config.h"

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
    m_snsStatus(false),
    m_altAvalible(false),
    m_insAvalible(false),
    m_snsAvalible(false)
{
    m_altTimer.setInterval(Config::value("Gui/BoardService/alt_timeout").toInt());
    m_insTimer.setInterval(Config::value("Gui/BoardService/ins_timeout").toInt());
    m_snsTimer.setInterval(Config::value("Gui/BoardService/sns_timeout").toInt());

    connect(&m_altTimer, &QTimer::timeout, this, &BoardService::onTimeout);
    connect(&m_insTimer, &QTimer::timeout, this, &BoardService::onTimeout);
    connect(&m_snsTimer, &QTimer::timeout, this, &BoardService::onTimeout);
}

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

bool BoardService::insStatus() const
{
    return m_insStatus;
}

bool BoardService::snsStatus() const
{
    return m_snsStatus;
}

bool BoardService::altAvalible() const
{
    return m_altAvalible;
}

bool BoardService::insAvalible() const
{
    return m_insAvalible;
}

bool BoardService::snsAvalible() const
{
    return m_snsAvalible;
}

void BoardService::updateAltData(const AltPacket& packet)
{
    if (!m_altAvalible)
    {
        m_altAvalible = true;
        emit altAvalibleChanged(m_altAvalible);
    }
    m_altTimer.start();

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
    if (!m_insAvalible)
    {
        m_insAvalible = true;
        emit insAvalibleChanged(m_insAvalible);
    }
    m_insTimer.start();

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
    if (!m_snsAvalible)
    {
        m_snsAvalible = true;
        emit snsAvalibleChanged(m_snsAvalible);
    }
    m_snsTimer.start();

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

void BoardService::onTimeout()
{
    if (this->sender() == &m_altTimer && m_altAvalible)
    {
        m_altAvalible = false;
        emit altAvalibleChanged(m_altAvalible);
    }
    else if (this->sender() == &m_insTimer && m_insAvalible)
    {
        m_insAvalible = false;
        emit snsAvalibleChanged(m_insAvalible);
    }
    else if (this->sender() == &m_snsTimer && m_snsAvalible)
    {
        m_snsAvalible = false;
        emit snsAvalibleChanged(m_snsAvalible);
    }
}


