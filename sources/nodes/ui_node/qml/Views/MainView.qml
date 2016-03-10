import QtQuick 2.5

Rectangle {
    id: main
    color: "#2c3e50"

    QtObject {
        id: topicsService
        objectName: "topicsService"

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
    }

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.margins: 4
        spacing: 4
        width: parent.width
        height: parent.height - status.height

        Column {
            id: dashboard
            anchors.top: parent.top
            spacing: 4

            FlightDirectorView {
                id: flightDirector
                pitch: topicsService.ins_pitch
                roll: topicsService.ins_roll
                yaw: topicsService.ins_yaw
                velocity: topicsService.sns_velocity
                altitude: topicsService.alt_altitude
            }

            VideoView {
                id: video
                width: parent.width
                height: width * 3 / 4
            }
        }

        MapView {
            id: map
            width: parent.width - dashboard.width
            height: parent.height
        }
    }
}
