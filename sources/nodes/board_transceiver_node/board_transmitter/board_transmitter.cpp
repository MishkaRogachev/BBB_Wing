#include "board_transmitter.h"

// Internal
#include "config.h"
#include "core.h"

#include "abstract_link.h"

#include "reverse_packet.h"
#include "crc_packet.h"

// Qt
#include <QTimerEvent>
#include <QBasicTimer>
#include <QDebug>

using namespace domain;

class BoardTransmitter::Impl
{
public:
    ReversePacket packet;

    QBasicTimer altTimer;
    QBasicTimer insTimer;
    QBasicTimer snsTimer;
    QBasicTimer controlTimer;

    int altInterval;
    int insInterval;
    int snsInterval;
    int controlInterval;
};

BoardTransmitter::BoardTransmitter(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->packet.altAvalible = false;
    d->packet.insAvalible = false;
    d->packet.snsAvalible = false;
    d->packet.controlAvalible = false;

    d->altInterval = Config::value("BoardTransceiver/alt_timeout").toInt();
    d->insInterval = Config::value("BoardTransceiver/ins_timeout").toInt();
    d->snsInterval = Config::value("BoardTransceiver/sns_timeout").toInt();
    d->controlInterval = Config::value("BoardTransceiver/ctrl_timeout").toInt();
}

BoardTransmitter::~BoardTransmitter()
{
    delete d;
}

void BoardTransmitter::transmit(AbstractLink* link)
{
    CrcPacket crcPacket(topics::reversePacket, d->packet.toByteArray());
    link->send(crcPacket.toByteArray());
}

void BoardTransmitter::setAltData(const QByteArray& data)
{
    d->packet.alt = AltPacket::fromByteArray(data);
    d->packet.altAvalible = true;
    d->altTimer.start(d->altInterval, Qt::PreciseTimer, this);
}

void BoardTransmitter::setInsData(const QByteArray& data)
{
    d->packet.ins = InsPacket::fromByteArray(data);
    d->packet.insAvalible = true;
    d->insTimer.start(d->insInterval, Qt::PreciseTimer, this);
}

void BoardTransmitter::setSnsData(const QByteArray& data)
{
    d->packet.sns = SnsPacket::fromByteArray(data);
    d->packet.snsAvalible = true;
    d->snsTimer.start(d->snsInterval, Qt::PreciseTimer, this);
}

void BoardTransmitter::setControlData(const QByteArray& data)
{
    d->packet.control = ControlPacket::fromByteArray(data);
    d->packet.controlAvalible = true;
    d->controlTimer.start(d->controlInterval, Qt::PreciseTimer, this);
}

void BoardTransmitter::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == d->altTimer.timerId())
    {
        d->packet.altAvalible = false;
        d->altTimer.stop();
    }
    if (event->timerId() == d->insTimer.timerId())
    {
        d->packet.insAvalible = false;
        d->altTimer.stop();
    }
    if (event->timerId() == d->snsTimer.timerId())
    {
        d->packet.snsAvalible = false;
        d->altTimer.stop();
    }
    if (event->timerId() == d->controlTimer.timerId())
    {
        d->packet.controlAvalible = false;
        d->altTimer.stop();
    }
}
