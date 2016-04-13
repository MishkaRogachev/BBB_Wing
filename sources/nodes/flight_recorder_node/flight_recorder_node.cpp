#include "flight_recorder_node.h"

// Qt
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QDataStream>
#include <QMap>
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"

#include "subscriber.h"

#include "crc_packet.h"

namespace
{
    const char* fileExtention = ".tlm";
}

using namespace domain;

class FlightRecorderNode::Impl
{
public:
    QFile file;
    Subscriber sub;

    QMap <QString, CrcPacket> packets;
};

FlightRecorderNode::FlightRecorderNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightRecorder/frequency").toFloat(),
                          parent),
    d(new Impl())
{}

FlightRecorderNode::~FlightRecorderNode()
{
    delete d;
}

void FlightRecorderNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::failuresHandler,
                       endpoints::navigator,
                       endpoints::controller,
                       endpoints::boardGateway });

    d->sub.subscribe(topics::all);
    connect(&d->sub, &Subscriber::received, this,
            &FlightRecorderNode::onSubReceived);
}

void FlightRecorderNode::exec()
{
    Config::begin("FlightRecorder");

    if (d->file.isOpen() &&
        (d->file.size() > Config::value("max_record_size").toInt() ||
         !d->file.exists())) d->file.close();

    if (!d->file.isOpen())
    {
        QString path = Config::value("path").toString();
        if (!QDir(path).exists()) QDir(path).mkpath(".");

        d->file.setFileName(path + QDateTime::currentDateTime().toString(
                            Config::value("file_format").toString()) +
                            ::fileExtention);

        d->file.open(QIODevice::Append);
    }

    if (d->file.isOpen())
    {
        for (const CrcPacket& packet: d->packets.values())
        {
             d->file.write(packet.toByteArray());
        }
        d->packets.clear();
    }

    Config::end();
}

void FlightRecorderNode::onSubReceived(const QString& topic,
                                       const QByteArray& data)
{
    d->packets.insert(topic, CrcPacket(topic, data));
}
