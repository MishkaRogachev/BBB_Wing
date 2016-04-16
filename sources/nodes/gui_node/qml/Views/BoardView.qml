import QtQuick 2.4

Column {
    id: dashboard

    spacing: 4
    width: 400

    FlightDirectorView {
        id: flightDirector
        width: parent.width
        pitch: boardService.pitch
        roll: boardService.roll
        yaw: boardService.yaw
        velocity: boardService.groundSpeed
        altitude: boardService.barAltitude
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 36

        Text {
            text: qsTr("ALT")
            font.bold: true
            font.pointSize: 14
            color: boardService.altStatus ? "#42CB6F" : "#ED5F55"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("INS")
            font.bold: true
            font.pointSize: 14
            color: boardService.insStatus ? "#42CB6F" : "#ED5F55"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("SNS")
            font.bold: true
            font.pointSize: 14
            color: boardService.snsStatus ? "#42CB6F" : "#ED5F55"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("FIX: ") + boardService.snsFix
            font.bold: true
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
