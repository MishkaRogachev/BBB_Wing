import QtQuick 2.5
import "../../Controls"

Rectangle {
    id: root
    height: 42
    color: palette.middlegroundColor

    Row {
        id: right
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 6
        spacing: 4

        Text {
            text: qsTr("Air")
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
            visible: groundService.airEnabled
        }

        Text {
            text: qsTr("Wire")
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
            visible: groundService.wireEnabled
        }

        Text {
            text: qsTr("PPS: ") + groundService.pps
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: qsTr("Bad: ") + groundService.badPackets + "%"
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            icon: "qrc:/resources/icons/settings.svg"
            text: qsTr("Settings")
            checkable: true
            onCheckedChanged: settings.visible = checked
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            icon: "qrc:/resources/icons/quit.svg"
            text: qsTr("Quit")
            onClicked: Qt.quit()
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
