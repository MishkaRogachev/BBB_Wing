import QtQuick 2.0
import "../Controls"

Rectangle {
    height: 48
    color: "#34495e"

    Row {
        id: right
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 6
        spacing: 4

        Clickable {
            icon: "qrc:/resources/icons/quit.svg"
            text: qsTr("Quit")
            onClicked: Qt.quit()
        }
    }
}
