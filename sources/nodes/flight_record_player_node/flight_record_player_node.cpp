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
    const QString timeTopic = "time_stamp";
}

using namespace domain;

class FlightRecordPlayerNode::Impl
{
public:
    QFile file;
    Publisher pub;
    QDateTime dateTime;

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
    d->dateTime = QDateTime::fromString(d->file.fileName().split(".").first(),
                                    Config::value("file_format").toString());

    QString headerLine = d->file.readLine();
    d->headers = headerLine.left(headerLine.length() - 1).split(
                     Config::value("delimiter").toString());

    Config::end();
}

void FlightRecordPlayerNode::exec()
{
    if (!d->file.isOpen()) this->init();
    if (!d->file.isOpen()) return;

    Config::begin("FlightRecordPlayer");

    QByteArray line = d->file.readLine();

    for (int i = 0; i < d->headers.length(); ++i)
    {
        int pos = line.indexOf(Config::value("delimiter").toString());
        if (pos == -1)
        {
            Config::end();
            return;
        }

        if (pos > 0)
        {
            QByteArray data = line.left(pos);
            if (i == 0)
            {
                QTime time = QTime::fromString(
                                 data, Config::value("time_format").toString());
                if (!time.isValid())
                {
                    Config::end();
                    return; // ingnore line if time is wrong
                }

                d->dateTime.setTime(time);
                // TODO: publish time
            }
            else
            {
                d->pub.publish(d->headers[i], data);
            }
        }
        line = line.mid(pos + 1);
    }
    Config::end();
}
