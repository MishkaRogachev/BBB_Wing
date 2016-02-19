import QtQuick 2.0

Rectangle {
    id: main
    color: "#2c3e50"

    MapView {
        id: map
        anchors.fill: parent
    }

    FlightDirectorView {
        id: flightDirector
        anchors.left: parent.left
        anchors.top: status.bottom
        anchors.margins: 4
    }

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
