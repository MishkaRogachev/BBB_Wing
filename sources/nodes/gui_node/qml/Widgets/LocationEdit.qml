import QtQuick 2.0
import "../Controls"

Row {
    id: root

    spacing: 6

    Column {
        spacing: 6
        anchors.verticalCenter: parent.verticalCenter

        Row {
            Label {
                width: 36
                text: qsTr("Lat.")
                anchors.verticalCenter: parent.verticalCenter
            }

            CoordSpinBox {
                id: latitude
                width: 172
            }
        }

        Row {
            Label {
                width: 36
                text: qsTr("Lon.")
                anchors.verticalCenter: parent.verticalCenter
            }

            CoordSpinBox {
                id: longitude
                width: 172
            }
        }
    }

    Button {
        anchors.verticalCenter: parent.verticalCenter
        icon: "qrc:/resources/icons/map-marker.svg"
    }
}
