import QtQuick 2.5
import "../Indicators"

Column {
    id: flightDirector

    property real pitch: 0.0
    property real roll: 0.0
    property real yaw: 0.0
    property real velocity: 0.0
    property real altitude: 0.0
    property bool pitchInverted: true
    property bool rollInverted: true

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        LinearScale {
            value: flightDirector.velocity
            minValue: flightDirector.velocity - 50
            maxValue: flightDirector.velocity + 50
            anchors.verticalCenter: parent.verticalCenter
            height: pithRoll.height - 16
            canvasRotation: 90
        }

        Item {
            id: pithRoll
            anchors.verticalCenter: parent.verticalCenter
            width: 240
            height: 240

            Horizont {
                id: horizont
                anchors.fill: parent
                pitch: pitchInverted ? -flightDirector.pitch : 0
                roll: rollInverted ? -flightDirector.roll : 0
            }

            PlaneMark {
                id: planeMark
                anchors.fill: parent
                pitch: pitchInverted ? 0 : flightDirector.pitch
                roll: rollInverted ? 0 : flightDirector.roll
            }
        }

        LinearScale {
            value: flightDirector.altitude
            minValue: flightDirector.altitude - 25
            maxValue: flightDirector.altitude + 25
            valueStep: 10
            anchors.verticalCenter: parent.verticalCenter
            height: pithRoll.height - 16
            canvasRotation: -90
        }

        // TODO: altitude scale
    }

    LinearScale {
        value: flightDirector.yaw
        minValue: flightDirector.yaw - 90
        maxValue: flightDirector.yaw + 90
        valueStep: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: flightDirector.width - 16
    }
}
