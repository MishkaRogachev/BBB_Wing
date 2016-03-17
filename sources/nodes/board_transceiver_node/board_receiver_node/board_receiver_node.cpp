#include "board_receiver_node.h"

// Internal
#include "topics.h"

#include "publisher.h"

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
    m_status = true;
    // TODO: receive ground station command
}
