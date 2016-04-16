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
    property int velocityStep: 5
    property int minPitch: -23
    property int maxPitch: 23
    property int minRoll: -45
    property int maxRoll: 45
    property int minAltitude: -27
    property int maxAltitude: 27
    property int altitudeStep: 10
    property int minYaw: -17
    property int maxYaw: 17

    property int rollOffset: 28
    spacing: 8

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on yaw { PropertyAnimation { duration: 100 } }
    Behavior on velocity { PropertyAnimation { duration: 100 } }
    Behavior on altitude { PropertyAnimation { duration: 100 } }

    Row {
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 8

        LinearScale {
            id: velocityScale
            value: flightDirector.velocity
            minValue: flightDirector.velocity + flightDirector.minVelocity
            maxValue: flightDirector.velocity + flightDirector.maxVelocity
            valueStep: flightDirector.velocityStep
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height + rollOffset
            canvasRotation: 90
        }

        Item {
            id: picthRoll
            anchors.verticalCenter: parent.verticalCenter
            width: flightDirector.width - velocityScale.width -
                   altitudeScale.width - row.spacing * 2
            height: width

            Item {
                id: pitchRollContents
                anchors.fill: parent
                visible: false

                Horizont {
                    id: horizont
                    anchors.fill: parent
                    effectiveHeight: pitchScale.height
                    pitch: pitchInverted ? flightDirector.pitch : 0
                    roll: rollInverted ? flightDirector.roll : 0
                    minPitch: flightDirector.minPitch
                    maxPitch: flightDirector.maxPitch
                }

                PitchScale {
                    id: pitchScale
                    anchors.centerIn: parent
                    height: parent.height - rollOffset - 48 // roll mark
                    pitch: flightDirector.pitch
                    roll: flightDirector.roll
                    minPitch: flightDirector.pitch + flightDirector.minPitch
                    maxPitch: flightDirector.pitch + flightDirector.maxPitch
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
                radius: width / 2
                visible: false
            }

            RollScale {
                anchors.centerIn: parent
                height: parent.height + rollOffset
                offset: rollOffset / 2
                roll: flightDirector.roll
                minRoll: flightDirector.minRoll
                maxRoll: flightDirector.maxRoll
            }
        }

        LinearScale {
            id: altitudeScale
            value: flightDirector.altitude
            minValue: flightDirector.altitude + flightDirector.minAltitude
            maxValue: flightDirector.altitude + flightDirector.maxAltitude
            valueStep: flightDirector.altitudeStep
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height + rollOffset
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
