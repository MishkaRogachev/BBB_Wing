import QtQuick 2.5

QtObject {
    id: nodeService

    property bool alt_status: false
    property bool ins_status: false
    property bool sns_status: false
    property int sns_fix: 0

    property string tr_line: "unknown"
    property int tr_pps: 0
    property int tr_bad: 0
}
