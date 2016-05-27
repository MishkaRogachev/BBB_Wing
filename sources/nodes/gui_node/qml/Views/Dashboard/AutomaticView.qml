import QtQuick 2.5
import "../../Controls"

Row {
    id: automatic
    spacing: 6

    Column {
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Switch {
            id: velocitySwitch
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Dial {
            id: velocityDial
            anchors.horizontalCenter: parent.horizontalCenter
            width: 96
        }
    }

    Column {
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Switch {
            id: headingSwitch
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Dial {
            id: headingDial
            anchors.horizontalCenter: parent.horizontalCenter
            width: 96
        }
    }

    Column {
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Switch {
            id: altitudeSwitch
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Dial {
            id: altitudeDial
            anchors.horizontalCenter: parent.horizontalCenter
            width: 96
        }
    }
}
