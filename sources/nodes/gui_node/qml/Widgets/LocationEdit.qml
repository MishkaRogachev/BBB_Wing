import QtQuick 2.0
import "../Controls"

Row {
    id: locationEdit

    property alias latitude: latitudeSpinBox.value
    property alias longitude: longitudeSpinBox.value

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
                id: latitudeSpinBox
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
                id: longitudeSpinBox
                width: 172
            }
        }
    }

    Button {
        id: pickButton
        anchors.verticalCenter: parent.verticalCenter
        icon: "qrc:/resources/icons/map-marker.svg"
        checkable: true
    }

    Connections {
        target: map
        onPicked: {
            if (!pickButton.checked) return;
            locationEdit.latitude = latitude;
            locationEdit.longitude = longitude;
            pickButton.checked = false;
        }
    }
}
