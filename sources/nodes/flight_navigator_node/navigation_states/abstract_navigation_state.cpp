#include "abstract_navigation_state.h"

// Internal
#include "topics.h"

using namespace domain;

AbstractNavigationState::AbstractNavigationState(NavigationStateData* data,
                                                 QObject* parent):
    QObject(parent),
    m_data(data)
{}

AbstractNavigationState::~AbstractNavigationState()
{}

void AbstractNavigationState::onSubReceived(const QString& topic,
                                            const QByteArray& msg)
{
    if (topic == topics::snsPacket) m_data->sns = SnsPacket::fromByteArray(msg);
    else if (topic == topics::insPacket) m_data->ins = InsPacket::fromByteArray(msg);
    else if (topic == topics::altimeterAltitude) m_data->altimeterAltitude = msg.toFloat();
}

void AbstractNavigationState::process()
{
    this->publish(topics::navigationState, this->stateId().toLatin1());
}
