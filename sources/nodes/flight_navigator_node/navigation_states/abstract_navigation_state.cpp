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
    if (topic == topics::snsLatitude) m_data->latitude = msg.toFloat();
    else if (topic == topics::snsLongitude) m_data->longitude = msg.toFloat();
    else if (topic == topics::altimeterAltitude) m_data->altimeterAltitude = msg.toFloat();
    else if (topic == topics::snsAltitude) m_data->snsAltitude = msg.toFloat();
    else if (topic == topics::snsVelocity) m_data->velocity= msg.toFloat();
    else if (topic == topics::snsClimb) m_data->climb = msg.toFloat();
    else if (topic == topics::insPitch) m_data->pitch = msg.toFloat();
    else if (topic == topics::insRoll) m_data->roll = msg.toFloat();
    else if (topic == topics::insYaw) m_data->yaw = msg.toFloat();
}

void AbstractNavigationState::process()
{
    this->publish(topics::navigationState, this->stateId().toLatin1());
}
