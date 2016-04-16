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

    property bool pitchInverted: configService.value("Gui/FlightDirector/pitchInverted")
    property bool rollInverted: configService.value("Gui/FlightDirector/rollInverted")
    property int rollOffset: configService.value("Gui/FlightDirector/rollOffset")
    spacing: configService.value("Gui/FlightDirector/spacing")

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on yaw { PropertyAnimation { duration: 100 } }
    Behavior on velocity { PropertyAnimation { duration: 100 } }
    Behavior on altitude { PropertyAnimation { duration: 100 } }

    Row {
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: flightDirector.spacing

        LinearScale {
            id: velocityScale
            value: flightDirector.velocity
            minValue: flightDirector.velocity +
                      parseInt(configService.value("Gui/FlightDirector/minVelocity"))
            maxValue: flightDirector.velocity +
                      parseInt(configService.value("Gui/FlightDirector/maxVelocity"))
            valueStep: configService.value("Gui/FlightDirector/velocityStep")
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
                    minPitch: configService.value("Gui/FlightDirector/minPitch")
                    maxPitch: configService.value("Gui/FlightDirector/maxPitch")
                }

                PitchScale {
                    id: pitchScale
                    anchors.centerIn: parent
                    height: parent.height - rollOffset - 48 // roll mark
                    pitch: flightDirector.pitch
                    roll: flightDirector.roll
                    minPitch: flightDirector.pitch + horizont.minPitch
                    maxPitch: flightDirector.pitch + horizont.maxPitch
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
                id: rollScale
                anchors.centerIn: parent
                height: parent.height + rollOffset
                offset: rollOffset / 2
                roll: flightDirector.roll
                minRoll: configService.value("Gui/FlightDirector/minRoll")
                maxRoll: configService.value("Gui/FlightDirector/maxRoll")
            }
        }

        LinearScale {
            id: altitudeScale
            value: flightDirector.altitude
            minValue: flightDirector.altitude +
                      parseInt(configService.value("Gui/FlightDirector/minAltitude"))
            maxValue: flightDirector.altitude +
                      parseInt(configService.value("Gui/FlightDirector/maxAltitude"))
            valueStep: configService.value("Gui/FlightDirector/altitudeStep")
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height + rollOffset
            canvasRotation: -90
        }
    }

    LinearScale {
        id: yawScale
        value: flightDirector.yaw
        minValue: flightDirector.yaw +
                  parseInt(configService.value("Gui/FlightDirector/minYaw"))
        maxValue: flightDirector.yaw +
                  parseInt(configService.value("Gui/FlightDirector/maxYaw"))
        valueStep: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: flightDirector.width - 16
    }
}
