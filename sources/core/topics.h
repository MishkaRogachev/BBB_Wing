#ifndef TOPICS_H
#define TOPICS_H

#include <QStringList>

namespace topics
{
    // TODO: refactor topic names by role(e.g. data, status)
    const QString altStatus = "alt_status";
    const QString altPacket = "alt_packet";

    const QString insStatus = "ins_status";
    const QString insPacket = "ins_packet";

    const QString snsStatus = "sns_status";
    const QString snsPacket = "sns_packet";

    const QString naviState = "navi_state";

    const QString flightCtrlPacket = "ctrl_packet";

    const QString connectionStatusPacket = "cn_status_packet";

    const QStringList boardTopics = {
        altStatus, altPacket,
        insStatus, insPacket,
        snsStatus, snsPacket,
        naviState,
        flightCtrlPacket
    };
}

#endif // TOPICS_H
