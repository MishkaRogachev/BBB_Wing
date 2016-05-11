#include "aircraft_control_factory.h"

// Qt
#include <QDebug>

// Internal
#include "throttle_control.h"
#include "aileron_control.h"
#include "elevator_control.h"
#include "rudder_control.h"
#include "elevon_control.h"

using namespace domain;

AbstractAircraftControl* AircraftControlFactory::create(const QVariantMap& settings)
{
    if (settings.value("type") == "throttle")
        return new ThrottleControl(settings.value("channel").toInt());
    if (settings.value("type") == "aileron")
        return new AileronControl(settings.value("channel").toInt(),
                                  (settings.value("wing").toString() == "left"),
                                  settings.value("roll_factor").toFloat());
    if (settings.value("type") == "elevator")
        return new ElevatorControl(settings.value("channel").toInt(),
                                   settings.value("pitch_factor").toFloat());
    if (settings.value("type") == "rudder")
        return new RudderControl(settings.value("channel").toInt());
    if (settings.value("type") == "elevon")
        return new ElevonControl(settings.value("channel").toInt(),
                                 (settings.value("wing").toString() == "left"),
                                 settings.value("roll_factor").toFloat(),
                                 settings.value("pitch_factor").toFloat());
    // TODO:
    // AirBrakeControl
    // DeceleronControl,
    // FlapControl,
    // FlaperonControl,
    // SpoilerControl,
    // ChassisBrake
    // ChassisRudder
    // etc
    return nullptr;
}
