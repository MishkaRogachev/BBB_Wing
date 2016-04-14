#include "ground_service.h"

using namespace domain;

GroundService::GroundService(QObject* parent):
    QObject(parent)
{}

bool GroundService::isAirEnabled() const
{
    return m_airEnabled;
}

bool GroundService::isWireEnabled() const
{
    return m_wireEnabled;
}

int GroundService::pps() const
{
    return m_pps;
}

int GroundService::badPackets() const
{
    return m_badPackets;
}

void GroundService::updateConnectionStatus(const ConnectionStatusPacket& packet)
{
    if (m_airEnabled != packet.airLink)
    {
        m_airEnabled = packet.airLink;
        emit airEnabledChanged(packet.airLink);
    }

    if (m_wireEnabled != packet.wireLink)
    {
        m_wireEnabled = packet.wireLink;
        emit wireEnabledChanged(packet.wireLink);
    }

    if (m_pps != packet.packetsPerSecond)
    {
        m_pps = packet.packetsPerSecond;
        emit ppsChanged(packet.packetsPerSecond);
    }

    if (m_badPackets != packet.packetsLost)
    {
        m_badPackets = packet.packetsLost;
        emit ppsChanged(packet.packetsLost);
    }
}
