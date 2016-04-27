import QtQuick 2.4
import "../../Indicators"
import "../../Controls"

Column {
    id: boardView

    spacing: 8
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
        width: parent.width - boardView.spacing
        anchors.horizontalCenter: parent.horizontalCenter
        height: width * 3 / 4
    }

    Joystick {
        anchors.horizontalCenter: parent.horizontalCenter

        width: configService.value("Gui/Joystick/size")
        minX: configService.value("Gui/Joystick/min_x")
        maxX: configService.value("Gui/Joystick/max_x")
        minY: configService.value("Gui/Joystick/min_y")
        maxY: configService.value("Gui/Joystick/max_y")

        onDeviationXChanged: console.log(deviationX, deviationY)
        onDeviationYChanged: console.log(deviationX, deviationY)
    }
}
