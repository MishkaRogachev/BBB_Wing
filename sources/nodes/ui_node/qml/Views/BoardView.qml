import QtQuick 2.4

Column {
    id: dashboard
    spacing: 4

    FlightDirectorView {
        id: flightDirector
        pitch: boardService.pitch
        roll: boardService.roll
        yaw: boardService.yaw
        velocity: boardService.velocity
        altitude: boardService.barAltitude
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            text: qsTr("FIX: ") + boardService.snsFix
            font.pointSize: 14
            color: "#ecf0f1"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    VideoView {
        id: video
        width: parent.width
        height: width * 3 / 4
    }
}
