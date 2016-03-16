import QtQuick 2.5
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

        Text {
            text: qsTr("PPS: ") + nodeService.tr_pps
            color: "#ecf0f1"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("Bad: ") + nodeService.tr_bad + "%"
            color: "#ecf0f1"
            anchors.verticalCenter: parent.verticalCenter
        }

        Clickable {
            icon: "qrc:/resources/icons/quit.svg"
            text: qsTr("Quit")
            onClicked: Qt.quit()
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
