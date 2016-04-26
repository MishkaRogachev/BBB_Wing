import QtQuick 2.5

Rectangle {
    id: joystick

    width: configService.value("Gui/Joystick/size")
    height: width
    color: "transparent"
    border.width: 2
    border.color: palette.highlightColor
    radius: width / 2

    Rectangle {
        id: handle
        x: (joystick.width - handle.width) / 2
        y: (joystick.height - handle.height) / 2
        width: joystick.width / 4
        height: width
        color: "transparent"
        border.width: 2
        border.color: palette.highlightColor
        radius: width / 2
    }

    MouseArea {
        anchors.fill: parent
        drag.target: handle
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.maximumX: joystick.width - handle.width
        drag.minimumY: 0
        drag.maximumY: joystick.height - handle.height
    }
}
