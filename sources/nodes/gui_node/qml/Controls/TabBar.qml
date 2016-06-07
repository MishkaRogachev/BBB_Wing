import QtQuick 2.6
import QtQuick.Controls 2.0

TabBar {
    id: tabBar

    property alias model: repeater.model

    Repeater {
        id: repeater

        TabButton {
            id: button
            text: modelData.text
            background: Rectangle {
                implicitWidth: 32
                implicitHeight: 32
                color: button.pressed || button.checked ?
                           palette.highlightColor : palette.backgroundColor
            }
        }
    }

    background: Rectangle {
        height: repeater.height
        color: palette.backgroundColor
    }
}
