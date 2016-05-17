import QtQuick 2.0
import "../Controls"

Row {
    id: root

    spacing: 6

    Repeater {
        model: [ "Latitude", "Longitude" ]

        Column {
            spacing: 6

            Text {
                text: modelData
                anchors.horizontalCenter: parent.horizontalCenter
            }

            SpinBox {
                id: degree
            }

            SpinBox {
                id: minutes
            }

            SpinBox {
                id: seconds
            }
        }
    }
}
