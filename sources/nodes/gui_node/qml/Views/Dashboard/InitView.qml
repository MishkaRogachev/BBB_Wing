import QtQuick 2.4
import "../../Controls"

Column {

    Row {
        spacing: 6

        Text {
            text: qsTr("Home point")
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        LocationEdit {
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            icon: "qrc:/resources/icons/map-marker.svg"
        }
    }

}
