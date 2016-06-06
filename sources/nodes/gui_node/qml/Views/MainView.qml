import QtQuick 2.6

import "../"
import "./Dashboard"
import "./Map"
import "./Settings"
import "./Status"

Rectangle {
    id: main
    color: palette.middlegroundColor

    Palette { id: palette }

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        DashboardView {
            id: boardView
            anchors.top: parent.top
        }

        Column {
            width: parent.width - boardView.width
            height: parent.height

            MapView {
                id: map
                width: parent.width
                height: parent.height * 2 / 3
            }
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
