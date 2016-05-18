import QtQuick 2.0
import "../Controls"

Row {
    id: root

    spacing: 6

    Column {
        spacing: 6
        anchors.verticalCenter: parent.verticalCenter
        //width: 156

        CoordSpinBox {
            id: latitude
           // width: parent.width
        }

        CoordSpinBox {
            id: longitude
///            width: parent.width
        }

        SpinBox {
            id: altitude
       //     width: parent.width
            from: -2000
            to: 10000
            stepSize: 1
        }
    }

    Button {
        anchors.verticalCenter: parent.verticalCenter
        icon: "qrc:/resources/icons/map-marker.svg"
    }
}
