import QtQuick 2.5
import Qt.labs.controls 1.0

Button {
    id: button

    property alias icon: image.source
    property alias backgroundColor: backgroundRect.color

    opacity: enabled ? 1 : 0.3

    background: Rectangle {
        id: backgroundRect
        implicitWidth: 32
        implicitHeight: 32
        color: button.pressed || button.checked ?
                   palette.highlightColor : palette.foregroundColor
    }

    label: Row {
        x: parent.leftPadding
        y: parent.topPadding
        height: parent.availableHeight

        Image {
            id: image
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            font: button.font
            text: button.text
            color: palette.textColor
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
