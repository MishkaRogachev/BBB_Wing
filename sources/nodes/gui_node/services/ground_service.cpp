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
    if (m_airEnabled != packet.airLine)
    {
        m_airEnabled = packet.airLine;
        emit airEnabledChanged(packet.airLine);
    }

    if (m_wireEnabled != packet.wireLine)
    {
        m_wireEnabled = packet.wireLine;
        emit wireEnabledChanged(packet.wireLine);
    }

    if (m_pps != packet.packetsPerSecond)
    {
        m_pps = packet.packetsPerSecond;
        emit ppsChanged(packet.packetsPerSecond);
    }

    if (m_badPackets != packet.badPackets)
    {
        m_badPackets = packet.badPackets;
        emit ppsChanged(packet.badPackets);
    }
}
