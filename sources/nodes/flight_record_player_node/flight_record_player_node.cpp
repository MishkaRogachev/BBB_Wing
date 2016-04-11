#include "flight_record_player_node.h"

// Qt
#include <QFile>
#include <QDateTime>
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"

#include "publisher.h"

namespace
{
    const char* delimiter = ",";
    const QString timeTopic = "time_stamp";
}

using namespace domain;

class FlightRecordPlayerNode::Impl
{
public:
    QFile file;
    Publisher pub;
    QDateTime time;

    QStringList headers;
};

FlightRecordPlayerNode::FlightRecordPlayerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightRecordPlayer/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->file.setFileName("08042016_1918.csv");

    d->pub.bind(endpoints::player);
}

FlightRecordPlayerNode::~FlightRecordPlayerNode()
{
    delete d;
}

void FlightRecordPlayerNode::init()
{
    Config::begin("FlightRecordPlayer");
    d->file.open(QIODevice::ReadOnly); // TODO: FlightRecordPlayerNode configuration
    d->time = QDateTime::fromString(d->file.fileName().split(".").first(),
                                    Config::value("file_format").toString());

    QString headerLine = d->file.readLine();
    d->headers = headerLine.left(headerLine.length() - 1).split(::delimiter[0]);

    Config::end();
}

void FlightRecordPlayerNode::exec()
{
    if (!d->file.isOpen()) this->init();
    if (!d->file.isOpen()) return;

    QByteArray line = d->file.readLine();

    for (int i = 0; i < d->headers.length(); ++i)
    {
        int pos = line.indexOf(::delimiter);
        if (pos == -1) return;
        if (pos > 0)
        {
            d->pub.publish(d->headers[i], line.left(pos));
        }
        line = line.mid(pos + 1);
    }
}
