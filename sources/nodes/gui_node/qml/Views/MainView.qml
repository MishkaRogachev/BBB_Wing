import QtQuick 2.5

import "../"
import "./Dashboard"
import "./Map"
import "./Settings"
import "./Status"

Rectangle {
    id: main
    color: palette.backgroundColor

    Palette { id: palette }

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 4

        DashboardView {
            id: boardView
            anchors.top: parent.top
        }

        MapView {
            id: map
            width: parent.width - boardView.width
            height: parent.height
        }
    }

    SettingsView {
        id: settings
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: false
    }

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
