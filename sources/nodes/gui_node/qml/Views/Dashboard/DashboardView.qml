import QtQuick 2.4
import "../../Indicators"

Column {
    id: boardView

    spacing: 4
    width: configService.value("Gui/Dashboard/width")

    FlightDirector {
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
            color: boardService.altStatus ? palette.errorColor : palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("INS")
            font.bold: true
            font.pointSize: 14
            color: boardService.insStatus ? palette.errorColor : palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("SNS")
            font.bold: true
            font.pointSize: 14
            color: boardService.snsStatus ? palette.errorColor : palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("FIX: ") + boardService.snsFix
            font.bold: true
            font.pointSize: 14
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    VideoView {
        id: video
        width: parent.width
        height: width * 3 / 4
    }
}
