#ifndef TOPICS_H
#define TOPICS_H

#include <QStringList>

namespace topics
{
    const QString status = "status";
    const QString data = "data";
    const QString all = "all";

    const QString altStatus = "status_alt";
    const QString altPacket = "data_alt";

    const QString insStatus = "status_ins";
    const QString insPacket = "data_ins";

    const QString snsStatus = "status_sns";
    const QString snsPacket = "data_sns";

    const QString naviState = "state_navi";

    const QString flightCtrlPacket = "data_ctrl";

    const QString connectionStatusPacket = "status_cn";

    const QStringList boardTopics = {
        altStatus, altPacket,
        insStatus, insPacket,
        snsStatus, snsPacket,
        naviState,
        flightCtrlPacket
    };
}

#endif // TOPICS_H
