import QtQuick 2.5

QtObject {
    id: nodeService

    property bool alt_status: false
    property real alt_altitude: 0.0
    property real alt_temperature: 0.0
    property bool ins_status: false
    property real ins_pitch: 0.0
    property real ins_roll: 0.0
    property real ins_yaw: 0.0
    property bool sns_status: false
    property int sns_fix: 0
    property real sns_latitude: 0.0
    property real sns_longitude: 0.0
    property real sns_velocity: 0.0

    property string tr_line: "unknown"
    property int tr_pps: 0
    property int tr_bad: 0
}
