import QtQuick 2.5

Rectangle {
    id: main
    color: "#2c3e50"

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Row {
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.margins: 4
        spacing: 4
        width: parent.width
        height: parent.height - status.height

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
}
