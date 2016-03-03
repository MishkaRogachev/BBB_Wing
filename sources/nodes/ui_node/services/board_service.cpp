#include "board_service.h"

using namespace domain;

class BoardService::Impl
{
public:
    float pitch = 0.0f;
    float roll = 0.0f;
    float yaw = 0.0f;
    float velocity = 0.0f;
    float altitude = 0.0f;
    float latitude = 0.0f; // TODO: convert to QGeoCoordinate, after topics grouping
    float longitude = 0.0f;
};

BoardService::BoardService(QObject* parent):
    QObject(parent),
    d(new BoardService::Impl)
{}

BoardService::~BoardService()
{
    delete d;
}

float BoardService::pitch() const
{
    return d->pitch;
}

float BoardService::roll() const
{
    return d->roll;
}

float BoardService::yaw() const
{
    return d->yaw;
}

float BoardService::velocity() const
{
    return d->velocity;
}

float BoardService::altitude() const
{
    return d->altitude;
}

float BoardService::latitude() const
{
    return d->latitude;
}

float BoardService::longitude() const
{
    return d->longitude;
}

void BoardService::setPitch(float pitch)
{
    if (d->pitch == pitch) return;

    d->pitch = pitch;
    emit pitchChanged(pitch);
}

void BoardService::setRoll(float roll)
{
    if (d->roll == roll) return;

    d->roll = roll;
    emit rollChanged(roll);
}

void BoardService::setYaw(float yaw)
{
    if (d->yaw == yaw) return;

    d->yaw = yaw;
    emit yawChanged(yaw);
}

void BoardService::setVelocity(float velocity)
{
    if (d->velocity == velocity) return;

    d->velocity = velocity;
    emit velocityChanged(velocity);
}

void BoardService::setAltitude(float altitude)
{
    if (d->altitude == altitude) return;

    d->altitude = altitude;
    emit altitudeChanged(altitude);
}

void BoardService::setLatitude(float latitude)
{
    if (d->latitude == latitude) return;

    d->latitude = latitude;
    emit latitudeChanged(latitude);
}

void BoardService::setLongitude(float longitude)
{
    if (d->longitude == longitude) return;

    d->longitude = longitude;
    emit longitudeChanged(longitude);
}
