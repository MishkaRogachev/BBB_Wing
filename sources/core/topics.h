#ifndef TOPICS_H
#define TOPICS_H

#include <QStringList>

namespace topics
{
//    TODO: topics must be grouped and minimized(local packets)1
    const QString altimeterStatus = "alt_status";
    const QString altimeterTemperature = "alt_temperature";
    const QString altimeterAltitude = "alt_altitude";

    const QString insStatus = "ins_status";
    const QString insPacket = "ins_packet";

    const QString snsStatus = "sns_status";
    const QString snsPacket = "sns_packet";

    const QString navigationState = "navi_state";

    const QString controlPitch = "ctrl_pitch";
    const QString controlRoll = "ctrl_roll";
    const QString controlVelocity = "ctrl_velocity";

    const QString transceiverStatus = "tr_status";
    const QString transceiverLine = "tr_line";
    const QString transceiverPps = "tr_pps";
    const QString transceiverBad = "tr_bad";

    const QStringList boardTopics = {
        altimeterStatus, altimeterAltitude, altimeterTemperature,
        insStatus, insPacket,
        snsStatus, snsPacket,
        navigationState,
        controlPitch, controlRoll, controlVelocity,
        transceiverStatus
    };
}

#endif // TOPICS_H
