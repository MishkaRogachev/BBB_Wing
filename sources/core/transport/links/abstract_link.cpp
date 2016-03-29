#include "abstract_link.h"

using namespace domain;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent)
{}

AbstractLink::~AbstractLink()
{}

void AbstractLink::tryTransmit(const QByteArray& packet)
{
    if (this->isConnected() || this->connect())
        this->transmit(packet);
}
