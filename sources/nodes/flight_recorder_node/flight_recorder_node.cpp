#include "flight_recorder_node.h"

// Qt
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>

// Internal
#include "config.h"
#include "subscriber.h"

namespace
{
    const char* delimiter = ",";
    const QString timeTopic = "time_stamp";
    const QStringList topics = {
        "alt_status", "alt_altitude", "alt_temperature",
        "sns_status", "sns_satellites", "sns_fix", "sns_latitude", "sns_longitude",
        "sns_course", "sns_velocity", "sns_altitude", "sns_climb" };
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
    Config::begin("FlightRecorder");
    QTextStream stream(&d->file);

    if (d->file.isOpen() && (d->file.size() > Config::setting("max_record_size")
        .toInt() || !d->file.exists())) d->file.close();

    if (!d->file.isOpen())
    {
        QString path = Config::setting("path").toString();
        if (!QDir(path).exists()) QDir(path).mkpath(".");

        d->file.setFileName(path + QDateTime::currentDateTime().toString(
                                "dd.MM.yyyy_hh:mm:ss") + ".csv");

        bool exists = d->file.exists();
        if (!d->file.open(QIODevice::Append | QIODevice::Text |
                          QIODevice::Unbuffered))
        {
            Config::end();
            return;
        }
        if (!exists) stream << ::timeTopic << ::delimiter <<
                               ::topics.join(::delimiter) << endl;
    }

    stream << QTime::currentTime().toString(
                  Config::setting("time_format").toString()).toLatin1();

    for (const QString& topic: ::topics)
        stream << ::delimiter << d->messages.value(topic);
    stream << endl;

    Config::end();
}

void FlightRecorderNode::onReceived(const QString& topic, const QByteArray& msg)
{
    d->messages[topic] = msg;
}
