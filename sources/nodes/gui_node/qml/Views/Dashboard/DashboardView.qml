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

        pitchInverted: configService.value("Gui/FlightDirector/pitch_inverted")
        rollInverted: configService.value("Gui/FlightDirector/roll_inverted")
        rollOffset: configService.value("Gui/FlightDirector/roll_offset")

        minVelocity: configService.value("Gui/FlightDirector/min_velocity")
        maxVelocity: configService.value("Gui/FlightDirector/max_velocity")
        velocityStep: configService.value("Gui/FlightDirector/velocity_step")
        minPitch: configService.value("Gui/FlightDirector/min_pitch")
        maxPitch: configService.value("Gui/FlightDirector/max_pitch")
        minRoll: configService.value("Gui/FlightDirector/min_roll")
        maxRoll: configService.value("Gui/FlightDirector/max_roll")
        minAltitude: configService.value("Gui/FlightDirector/min_altitude")
        maxAltitude: configService.value("Gui/FlightDirector/max_altitude")
        altitudeStep: configService.value("Gui/FlightDirector/altitude_step")
        minYaw: configService.value("Gui/FlightDirector/min_yaw")
        maxYaw: configService.value("Gui/FlightDirector/max_yaw")
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

        onDeviationXChanged: boardService.setJoystickDeviationX(deviationX)
        onDeviationYChanged: boardService.setJoystickDeviationY(deviationY)
    }
}
