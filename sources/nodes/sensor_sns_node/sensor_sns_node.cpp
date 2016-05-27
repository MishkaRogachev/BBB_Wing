#include "sensor_sns_node.h"

// Gpsd
#include <libgpsmm.h>

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"
#include "sns_packet.h"

#include "publisher.h"

using namespace domain;

class SensorSnsNode::Impl
{
public:
    gpsmm handle = gpsmm("localhost", DEFAULT_GPSD_PORT);
    Publisher pub;
};

SensorSnsNode::SensorSnsNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorSns/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::sns);
}

SensorSnsNode::~SensorSnsNode()
{
    delete d;
}

void SensorSnsNode::init()
{
    d->handle.stream(WATCH_ENABLE | WATCH_JSON);
}

void SensorSnsNode::exec()
{
    struct gps_data_t* data = nullptr;
    SnsPacket packet;

    if (!d->handle.is_open() || ((data = d->handle.read()) == nullptr))
    {
        packet.status = false;
        this->init();
    }
    else
    {
        packet.status = true;

        if (data->status)
        {
            packet.fix = data->fix.mode;

            if (data->fix.mode > 1)
            {
                packet.fix2d.latitude = data->fix.latitude;
                packet.fix2d.longitude = data->fix.longitude;
                packet.fix2d.yaw = data->fix.track;
                packet.fix2d.groundSpeed = data->fix.speed;

                if (data->fix.mode > 2)
                {
                    packet.fix3d.altitude = data->fix.altitude;
                    packet.fix3d.climb = data->fix.climb;
                }
            }
        }
        else packet.fix = 0;
    }
    d->pub.publish(topics::snsPacket, packet.toByteArray());
}
