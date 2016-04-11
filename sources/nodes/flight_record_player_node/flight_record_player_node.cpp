#include "flight_record_player_node.h"

// Qt
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>

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
};

FlightRecordPlayerNode::FlightRecordPlayerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightRecordPlayer/frequency").toFloat(),
                          parent),
    d(new Impl())
{}

FlightRecordPlayerNode::~FlightRecordPlayerNode()
{
    delete d;
}

void FlightRecordPlayerNode::init()
{

}

void FlightRecordPlayerNode::exec()
{

}
