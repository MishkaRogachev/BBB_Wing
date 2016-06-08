#include "flight_recorder_node.h"

// Qt
#include <QDateTime>
#include <QDataStream>
#include <QMap>
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"

#include "subscriber.h"

#include "recorders/file_recorder.h"

namespace
{
    const char* fileExtention = ".tlm";
}

using namespace domain;

class FlightRecorderNode::Impl
{
public:
    Subscriber sub;

    QString filename;
    FileRecorder recorder;
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
                       endpoints::navigator,
                       endpoints::flightPilot,
                       endpoints::boardTransceiver });

    d->sub.subscribe(topics::all);
    connect(&d->sub, &Subscriber::received, this,
            &FlightRecorderNode::onSubReceived);
}

void FlightRecorderNode::start()
{
    d->filename = QDateTime::currentDateTime().toString(
                       Config::value("FlightRecorder/file_format").toString() +
                       ::fileExtention);
    d->recorder.open(d->filename);

    AbstractNodeFrequency::start();
}

void FlightRecorderNode::exec()
{
    if (!d->recorder.isAvalible())
    {
        d->recorder.open(d->filename);
        d->recorder.flush();
    }
}

void FlightRecorderNode::onSubReceived(const QString& topic,
                                       const QByteArray& data)
{
    d->recorder.addRecord(RecordPacket(topic, data));
}
