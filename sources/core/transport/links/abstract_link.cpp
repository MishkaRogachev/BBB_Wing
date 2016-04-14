#include "abstract_link.h"

// Qt
#include <QTimer>

namespace
{
    const int interval = 2000;
}

using namespace domain;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent),
    m_online(false),
    m_timer(new QTimer(this))
{
    m_timer->start(::interval);
}

AbstractLink::~AbstractLink()
{}

bool AbstractLink::isOnline() const
{
    return m_online;
}

void AbstractLink::onReceived(const QByteArray& packet)
{
    m_timer->start();

    m_online = true;
    emit received(packet);
}

void AbstractLink::onTimeout()
{
    m_online = false;
    emit timeout();
}
