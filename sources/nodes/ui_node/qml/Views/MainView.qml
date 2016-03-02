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
        width: parent.width
        height: parent.height - status.height

        Column {
            id: dashboard
            anchors.top: parent.top

            FlightDirectorView {
                id: flightDirector
                pitch: boardService.pitch
                roll: boardService.roll
                yaw: boardService.yaw
            }
        }

        MapView {
            id: map
            width: parent.width - dashboard.width
            height: parent.height
        }
    }
}
