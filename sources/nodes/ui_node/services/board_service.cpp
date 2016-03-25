#include "board_service.h"

using namespace domain;

BoardService::BoardService(QObject* parent):
    QObject(parent),
    m_position(),
    m_velocity(0),
    m_climb(0),
    m_snsAltitude(0),
    m_yaw(0)
{}

QGeoCoordinate BoardService::position() const
{
    return m_position;
}

float BoardService::velocity() const
{
    return m_velocity;
}

float BoardService::climb() const
{
    return m_climb;
}

float BoardService::snsAltitude() const
{
    return m_snsAltitude;
}

float BoardService::yaw() const
{
    return m_yaw;
}

void BoardService::updateSnsData(const SnsPacket& packet)
{
    QGeoCoordinate position(packet.latitude, packet.longitude, packet.altitude);
    if (m_position != position)
    {
        m_position = position;
        emit positionChanged(position);
    }

    if (!qFuzzyCompare(m_velocity, packet.velocity))
    {
        m_velocity = packet.velocity;
        emit velocityChanged(packet.velocity);
    }

    if (!qFuzzyCompare(m_climb, packet.climb))
    {
        m_climb = packet.climb;
        emit climbChanged(packet.climb);
    }

    if (!qFuzzyCompare(m_snsAltitude, packet.altitude))
    {
        m_snsAltitude = packet.altitude;
        emit velocityChanged(packet.altitude);
    }

    if (!qFuzzyCompare(m_yaw, packet.yaw))
    {
        m_yaw = packet.yaw;
        emit yawChanged(packet.yaw);
    }
}
