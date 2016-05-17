import QtQuick 2.6
import Qt.labs.controls 1.0

SpinBox {
    id: spinBox

    leftPadding: -background.implicitWidth / 2
    opacity: enabled ? 1 : 0.3

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 32
        color: palette.backgroundColor
    }

    contentItem: TextInput {
        text: textFromValue(parent.value, parent.locale)

        font: parent.font
        color: palette.textColor
        selectionColor: palette.highlightColor
        selectedTextColor: color
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        validator: parent.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    down.indicator: Rectangle {
        x: parent.mirrored ? up.indicator.width : parent.width - width - up.indicator.width
        height: parent.height
        implicitWidth: 32
        implicitHeight: 32
        color: down.pressed ? palette.highlightColor : "transparent"

        Image {
            anchors.centerIn: parent
            opacity: enabled ? 1 : 0.5
            source: "qrc:/resources/icons/minus.svg"
        }
    }

    up.indicator: Rectangle {
        x: parent.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 32
        implicitHeight: 32
        color: up.pressed ? palette.highlightColor : palette.transparent

        Image {
            anchors.centerIn: parent
            opacity: enabled ? 1 : 0.5
            source: "qrc:/resources/icons/plus.svg"
        }
    }
}

