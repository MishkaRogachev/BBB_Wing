import QtQuick 2.0
import "../Indicators"

Column {
    id: flightDirector

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        Horizont {
            id: horizont
            anchors.verticalCenter: parent.verticalCenter
            width: 240
            height: 240
        }
    }
}
