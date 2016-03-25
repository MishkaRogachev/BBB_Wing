import QtQuick 2.5
import "../Services"

Rectangle {
    id: main
    color: "#2c3e50"

    NodeService {
        id: nodeService
        objectName: "nodeService"
    }

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

        Column {
            id: dashboard
            anchors.top: parent.top
            spacing: 4

            FlightDirectorView {
                id: flightDirector
                pitch: boardService.pitch
                roll: boardService.roll
                yaw: boardService.yaw
                velocity: boardService.velocity
                altitude: nodeService.alt_altitude
            }

            VideoView {
                id: video
                width: parent.width
                height: width * 3 / 4
            }
        }

        MapView {
            id: map
            width: parent.width - dashboard.width
            height: parent.height
        }
    }
}
