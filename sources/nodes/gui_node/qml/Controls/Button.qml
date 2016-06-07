import QtQuick 2.6
import QtQuick.Controls 2.0

Button {
    id: button

    property alias icon: image.source
    property alias backgroundColor: backgroundRect.color

    opacity: enabled ? 1 : 0.3
    font.pointSize: 11

    background: Rectangle {
        id: backgroundRect
        implicitWidth: 32
        implicitHeight: 32
        color: button.pressed || button.checked ?
                   palette.highlightColor : palette.foregroundColor
    }

    contentItem: Item {
        implicitWidth: row.width
        implicitHeight: row.height

        Row {
            id: row
            anchors.centerIn: parent
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
}
