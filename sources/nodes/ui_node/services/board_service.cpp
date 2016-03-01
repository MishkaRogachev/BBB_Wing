#include "board_service.h"

using namespace domain;

class BoardService::Impl
{
public:
    float pitch = 0.0f;
    float roll = 0.0f;
    float yaw = 0.0f;
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
