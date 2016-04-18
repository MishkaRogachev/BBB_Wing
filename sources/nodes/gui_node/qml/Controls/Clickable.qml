import QtQuick 2.5

Item {
    id: clickable

    property alias text: label.text
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
            id: label
            font.pointSize: 11
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: clickable.clicked()
    }
}
