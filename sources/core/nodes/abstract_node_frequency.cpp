#include "abstract_node_frequency.h"

// Qt
#include <QTimerEvent>

using namespace domain;

AbstractNodeFrequency::AbstractNodeFrequency(QObject* parent):
    AbstractNode(parent),
    m_timerId(0)
{}

void AbstractNodeFrequency::start(float frequency)
{
    if (m_timerId) this->stop();

    m_timerId = this->startTimer(1000 / frequency, Qt::PreciseTimer);
}

void AbstractNodeFrequency::stop()
{
    this->killTimer(m_timerId);
    m_timerId = 0;
}

void AbstractNodeFrequency::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_timerId) return;

    this->exec();
}
