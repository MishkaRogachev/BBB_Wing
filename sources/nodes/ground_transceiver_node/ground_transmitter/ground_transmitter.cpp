#include "ground_transmitter.h"

// Internal
#include "core.h"
#include "abstract_link.h"
#include "crc_packet.h"

using namespace domain;

GroundTransmitter::GroundTransmitter(QObject* parent):
    QObject(parent)
{}

void GroundTransmitter::transmit(AbstractLink* link)
{
    CrcPacket crcPacket(topics::reversePacket, m_packet.toByteArray());
    link->send(crcPacket.toByteArray());
}

void GroundTransmitter::setManualData(const QByteArray& data)
{
    m_packet.isManual = true;
    m_packet.manual = ControlPacket::fromByteArray(data);
}

void GroundTransmitter::setAutomaticData(const QByteArray& data)
{
    m_packet.isManual = false;
    m_packet.automatic = AutomaticControlPacket::fromByteArray(data);
}
