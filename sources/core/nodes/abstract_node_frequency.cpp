#include "abstract_node_frequency.h"

// Qt
#include <QTimerEvent>

using namespace domain;

AbstractNodeFrequency::AbstractNodeFrequency(float frequency, QObject* parent):
    AbstractNode(parent),
    m_timerId(0),
    m_frequency(frequency)
{}

float AbstractNodeFrequency::frequency() const
{
    return m_frequency;
}

void AbstractNodeFrequency::start()
{
    if (m_timerId) this->stop();

    m_timerId = this->startTimer(1000 / m_frequency, Qt::PreciseTimer);
}

void AbstractNodeFrequency::stop()
{
    this->killTimer(m_timerId);
    m_timerId = 0;
}

void AbstractNodeFrequency::setFrequency(float frequency)
{
    m_frequency = frequency;
}

void AbstractNodeFrequency::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_timerId) return;

    this->exec();
}
