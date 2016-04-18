import QtQuick 2.5
import "./Settings"

Rectangle {
    id: main
    color: "#2c3e50"

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 4

        BoardView {
            id: boardView
            anchors.top: parent.top
        }

        MapView {
            id: map
            width: parent.width - boardView.width
            height: parent.height
        }
    }

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    SettingsView {
        id: settings
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: false
    }
}
