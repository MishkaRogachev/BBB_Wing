#include "flight_record_player_node.h"

// Qt
#include <QFile>
#include <QDateTime>
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"

#include "publisher.h"

#include "transmission_packet.h"

using namespace domain;

class FlightRecordPlayerNode::Impl
{
public:
    QFile file;
    Publisher pub;
    QDateTime dateTime;
};

FlightRecordPlayerNode::FlightRecordPlayerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightRecordPlayer/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->file.setFileName(Config::value("FlightRecordPlayer/filename").toString());

    d->pub.bind(endpoints::player);
}

FlightRecordPlayerNode::~FlightRecordPlayerNode()
{
    delete d;
}

void FlightRecordPlayerNode::init()
{
    d->file.open(QIODevice::ReadOnly);
    d->dateTime = QDateTime::fromString(
                      d->file.fileName().split(".").first(),
                      Config::value("FlightRecordPlayer/file_format").toString());
}

void FlightRecordPlayerNode::exec()
{
    if (!d->file.isOpen()) this->init();
    if (!d->file.isOpen() || d->file.atEnd()) return;

    QDataStream stream(&d->file);

    TransmissionPacket packet;
    stream >> packet;

    if (packet.validateCrc()) d->pub.publish(packet.topic, packet.data);
}
