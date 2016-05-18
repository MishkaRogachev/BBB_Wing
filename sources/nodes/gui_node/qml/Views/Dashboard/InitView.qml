import QtQuick 2.4
import "../../Widgets"
import "../../Controls"

Column {
    spacing: 6

    Row {
        spacing: 6

        Text {
            text: qsTr("Home point")
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Column {
            spacing: 6
            anchors.verticalCenter: parent.verticalCenter

            LocationEdit {
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                Label {
                    width: 36
                    text: qsTr("Alt.")
                    anchors.verticalCenter: parent.verticalCenter
                }

                SpinBox {
                    id: altitude
                    width: 172
                    from : -1000
                    to: 15000
                }
            }
        }
    }

}
