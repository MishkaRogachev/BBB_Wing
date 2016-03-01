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

        // TODO: velocity scale

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

        // TODO: altitude scale
    }

    // TODO: yaw scale
}
