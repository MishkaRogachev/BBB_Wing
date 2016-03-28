#include "flight_recorder_node.h"

// Qt
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>

// Internal
#include "topics.h"
#include "config.h"
#include "subscriber.h"

namespace
{
    const char* delimiter = ",";
    const QString timeTopic = "time_stamp";
}

using namespace domain;

class FlightRecorderNode::Impl
{
public:
    QFile file;
    QMap<QString, QByteArray> messages;
    Subscriber sub;
};

FlightRecorderNode::FlightRecorderNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

FlightRecorderNode::~FlightRecorderNode()
{
    delete d;
}

void FlightRecorderNode::init()
{
     d->sub.connectTo("ipc://alt");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this,
             &FlightRecorderNode::onSubReceived);
}

void FlightRecorderNode::exec()
{
    Config::begin("FlightRecorder");
    QTextStream stream(&d->file);

    if (d->file.isOpen() && (d->file.size() > Config::value("max_record_size")
        .toInt() || !d->file.exists())) d->file.close();

    if (!d->file.isOpen())
    {
        QString path = Config::value("path").toString();
        if (!QDir(path).exists()) QDir(path).mkpath(".");

        d->file.setFileName(path + QDateTime::currentDateTime().toString(
                           Config::value("file_format").toString()) + ".csv");

        bool exists = d->file.exists();
        if (!d->file.open(QIODevice::Append | QIODevice::Text |
                          QIODevice::Unbuffered))
        {
            Config::end();
            return;
        }
        if (!exists) stream << ::timeTopic << ::delimiter <<
                               topics::boardTopics.join(::delimiter) << endl;
    }

    stream << QTime::currentTime().toString(
                  Config::value("time_format").toString()).toLatin1();

    for (const QString& topic: topics::boardTopics)
        stream << ::delimiter << d->messages.value(topic);
    stream << endl;

    Config::end();
}

void FlightRecorderNode::onSubReceived(const QString& topic,
                                       const QByteArray& msg)
{
    d->messages[topic] = msg;
}
