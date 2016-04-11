#ifndef CORE_H
#define CORE_H

#include <QStringList>

namespace topics
{
    const QString status = "status";
    const QString data = "data";
    const QString all = "";

    const QString interview = "iv";

    const QString altStatus = "status_alt";
    const QString altPacket = "data_alt";

    const QString insStatus = "status_ins";
    const QString insPacket = "data_ins";

    const QString snsStatus = "status_sns";
    const QString snsPacket = "data_sns";

    const QString failuresPacket = "data_fails";

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

namespace endpoints
{
    const QString altimeter = "ipc://alt";
    const QString ins = "ipc://ins";
    const QString sns = "ipc://sns";

    const QString failuresHandler = "ipc://failurer";

    const QString navigator = "ipc://navi";
    const QString controller = "ipc://ctrl";

    const QString player = "ipc://player";

    const QString boardGateway = "ipc://board_gw";
    const QString groundGateway = "ipc://ground_gw";

    const QString gui = "ipc://gui";
} 

#endif // CORE_H
