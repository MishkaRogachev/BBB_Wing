import QtQuick 2.0
import "../Indicators"

Column {
    id: flightDirector

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: pithRoll
            anchors.verticalCenter: parent.verticalCenter
            width: 240
            height: 240

            Horizont {
                id: horizont
                anchors.fill: parent
            }

            Image {
                id: planeMark
                anchors.centerIn: parent
                source: "qrc:/resources/indicators/plane_horizont_mark.svg"
            }
        }
    }
}
