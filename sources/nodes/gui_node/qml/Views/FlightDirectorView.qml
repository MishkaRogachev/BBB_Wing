import QtQuick 2.5
import QtGraphicalEffects 1.0
import "../Indicators"

Column {
    id: flightDirector

    property real pitch: 0.0
    property real roll: 0.0
    property real yaw: 0.0
    property real velocity: 0.0
    property real altitude: 0.0

    // TODO: to settings
    property bool pitchInverted: true
    property bool rollInverted: true
    property int minVelocity: -13
    property int maxVelocity: 13
    property int minPitch: -37
    property int maxPitch: 37
    property int minAltitude: -27
    property int maxAltitude: 27
    property int minYaw: -17
    property int maxYaw: 17

    property alias radius: mask.radius
    property alias size: picthRoll.width

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on yaw { PropertyAnimation { duration: 100 } }
    Behavior on velocity { PropertyAnimation { duration: 100 } }
    Behavior on altitude { PropertyAnimation { duration: 100 } }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        LinearScale {
            value: flightDirector.velocity
            minValue: flightDirector.velocity + flightDirector.minVelocity
            maxValue: flightDirector.velocity + flightDirector.maxVelocity
            valueStep: 5
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height - 16
            canvasRotation: 90
        }

        Item {
            id: picthRoll
            anchors.verticalCenter: parent.verticalCenter
            width: 256
            height: width

            Item {
                id: pitchRollContents
                anchors.fill: parent
                visible: false

                Horizont {
                    id: horizont
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height + 100
                    pitch: pitchInverted ? flightDirector.pitch : 0
                    roll: rollInverted ? flightDirector.roll : 0
                    minPitch: flightDirector.minPitch
                    maxPitch: flightDirector.maxPitch
                }

                PitchScale {
                    anchors.centerIn: parent
                    height: parent.height + 100
                    pitch: flightDirector.pitch
                    roll: flightDirector.roll
                    minPitch: flightDirector.pitch + flightDirector.minPitch
                    maxPitch: flightDirector.pitch + flightDirector.maxPitch
                }

                RollScale {
                    anchors.centerIn: parent
                    height: parent.height
                }

                PlaneMark { // TODO: plane mark pitch & roll
                    anchors.centerIn: parent
                    pitch: pitchInverted ? 0 : flightDirector.pitch
                    roll: rollInverted ? 0 : flightDirector.roll
                }
            }

            OpacityMask {
                anchors.fill: parent
                source: pitchRollContents
                maskSource: mask
            }

            Rectangle {
                id: mask
                width: parent.width
                height: parent.height
                radius: width / 8
                visible: false
            }
        }

        LinearScale {
            value: flightDirector.altitude
            minValue: flightDirector.altitude + flightDirector.minAltitude
            maxValue: flightDirector.altitude + flightDirector.maxAltitude
            valueStep: 10
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height - 16
            canvasRotation: -90
        }
    }

    LinearScale {
        value: flightDirector.yaw
        minValue: flightDirector.yaw + flightDirector.minYaw
        maxValue: flightDirector.yaw + flightDirector.maxYaw
        valueStep: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: flightDirector.width - 16
    }
}
