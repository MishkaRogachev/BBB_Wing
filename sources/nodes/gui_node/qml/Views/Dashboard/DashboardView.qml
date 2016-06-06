import QtQuick 2.6
import "../../Controls"
import "../../Indicators"

Column {
    id: dashboardView

    spacing: configService.value("Gui/Dashboard/spacing")
    width: configService.value("Gui/Dashboard/width")

    FlightDirector {
        id: flightDirector
        width: parent.width
        spacing: dashboardView.spacing

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
            color: boardService.altAvalible ? palette.textColor : palette.errorColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("INS")
            font.bold: true
            font.pointSize: 14
            color: boardService.insAvalible ? palette.textColor : palette.errorColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("FIX: ") + boardService.snsFix
            font.bold: true
            font.pointSize: 14
            color: boardService.snsAvalible ? palette.textColor : palette.errorColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    VideoView {
        id: video
        width: parent.width - dashboardView.spacing
        anchors.horizontalCenter: parent.horizontalCenter
        height: width * 3 / 4
    }

    Component {
        id: initComponent

        InitView {
            id: init
        }
    }

    Component {
        id: automaticComponent

        AutomaticView {
            id: automatic
        }
    }

    Component {
        id: manualComponent

        ManualView {
            id: manual
        }
    }

    TabBar {
        id: modeBar
        anchors.horizontalCenter: parent.horizontalCenter
        property variant currentModelItem: model[currentIndex]
        width: parent.width - dashboardView.spacing
        model: [
            { text: qsTr("INIT"), component: initComponent },
            { text: qsTr("AUTOMATIC"), component: automaticComponent },
            { text:qsTr("MANUAL"), component: manualComponent }
        ]
    }

    Loader {
        anchors.horizontalCenter: parent.horizontalCenter
        sourceComponent: modeBar.currentModelItem.component
    }
}
