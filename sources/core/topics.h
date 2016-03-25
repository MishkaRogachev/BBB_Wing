#ifndef TOPICS_H
#define TOPICS_H

#include <QStringList>

namespace topics
{
    const QString altStatus = "alt_status";
    const QString altPacket = "alt_packet";

    const QString insStatus = "ins_status";
    const QString insPacket = "ins_packet";

    const QString snsStatus = "sns_status";
    const QString snsPacket = "sns_packet";

    const QString naviState = "navi_state";

    const QString controlPitch = "ctrl_pitch";
    const QString controlRoll = "ctrl_roll";
    const QString controlVelocity = "ctrl_velocity";

    const QString transceiverStatus = "tr_status";
    const QString transceiverLine = "tr_line";
    const QString transceiverPps = "tr_pps";
    const QString transceiverBad = "tr_bad";

    const QStringList boardTopics = {
        altStatus, altPacket,
        insStatus, insPacket,
        snsStatus, snsPacket,
        naviState,
        controlPitch, controlRoll, controlVelocity,
        transceiverStatus
    };
}

#endif // TOPICS_H
