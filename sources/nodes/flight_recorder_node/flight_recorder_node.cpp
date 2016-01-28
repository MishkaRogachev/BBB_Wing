#include "flight_recorder_node.h"

// Qt
#include <QDebug>
#include <QFile>
#include <QDateTime>

// Internal
#include "config.h"
#include "subscriber.h"

namespace
{
    const char* delimiter = ",";
    const QStringList topics = {
        "time_stamp",
        "alt_status", "alt_altitude", "alt_temperature",
        "sns_status", "sns_status", "sns_fix", "sns_fix_mode",
        "sns_latitude", "sns_longitude", "sns_course", "sns_velocity",
        "sns_altitude", "sns_climb" };
}

using namespace domain;

class FlightRecorderNode::Impl
{
public:
    Subscriber sub;
    QFile file;
    QMap<QString, QByteArray> messages;
};

FlightRecorderNode::FlightRecorderNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{}

FlightRecorderNode::~FlightRecorderNode()
{
    delete d;
}

void FlightRecorderNode::init()
{
     d->sub.connectTo("ipc://altimeter");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this, &FlightRecorderNode::onReceived);
}

void FlightRecorderNode::exec()
{
    QTextStream stream(&d->file);
    if (!d->file.isOpen())
    {
        d->file.setFileName(Config::setting("FlightRecorder/path").toString() +
                            QDateTime::currentDateTime().toString(
                                "dd.MM.yyyy_hh:mm:ss") + ".csv");
        bool exists = d->file.exists();
        if (!d->file.open(QIODevice::Append | QIODevice::Text))
            return;
        if (!exists) stream << ::topics.join(::delimiter) << endl;
    }

    d->messages["time_stamp"] = QTime::currentTime().toString(
                                    "hh:mm:ss.zzz").toLatin1();
    QList<QByteArray> buffer;
    for (const QString& topic: ::topics)
        buffer.append(d->messages.value(topic));

    stream << buffer.join(::delimiter) << endl;
    stream.flush();
}

void FlightRecorderNode::onReceived(const QString& topic, const QByteArray& msg)
{
    d->messages[topic] = msg;
}
