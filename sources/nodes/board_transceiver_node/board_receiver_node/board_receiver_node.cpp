#include "board_receiver_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "publisher.h"
#include "ground_packet.h"

using namespace domain;

BoardReceiverNode::BoardReceiverNode(float frequency, Publisher* pub,
                                     QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    m_pub(pub),
    m_status(false)
{}

void BoardReceiverNode::exec()
{
    m_pub->publish(topics::transceiverStatus, QByteArray::number(m_status));
    m_status = false;
}

void BoardReceiverNode::onPacketReceived(const QByteArray& packetData)
{
    QDataStream stream(packetData);
    GroundPacket packet;
    stream >> packet;

    qDebug() << packetData;

    if (!packet.validateCrc()) return;
    m_status = true;

    // TODO: publish ground packet data
}
