import QtQuick 2.0

Item {
    id: clickable

    property alias text: lable.text
    property alias icon: image.source
    property alias pressed: mouseArea.pressed

    signal clicked()

    width: contents.width + 16
    height: 48

    Rectangle {
        id: hightlight
        anchors.fill: parent
        color: "#66ecf0f1"
        visible: clickable.pressed
    }

    Row {
        id: contents
        anchors.centerIn: parent

        Image {
            id: image
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: lable
            color: "#ecf0f1"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: clickable.clicked()
    }
}
