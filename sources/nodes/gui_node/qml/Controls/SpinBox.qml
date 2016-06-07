import QtQuick 2.6
import QtQuick.Controls 2.0

SpinBox {
    id: spinBox

    font.pointSize: 11
    leftPadding: 6 - (up.indicator.width + down.indicator.width) / 2
    opacity: enabled ? 1 : 0.3

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 32
        color: palette.backgroundColor
    }

    contentItem: TextInput {
        text: textFromValue(spinBox.value, spinBox.locale)
        onEditingFinished:spinBox.value = valueFromText(text, spinBox.locale)
        font: spinBox.font
        color: palette.textColor
        selectionColor: palette.highlightColor
        selectedTextColor: color
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        validator: spinBox.validator
    }

    down.indicator: Rectangle {
        x: spinBox.mirrored ? up.indicator.width :
                              spinBox.width - width - up.indicator.width
        height: spinBox.height
        implicitWidth: 32
        implicitHeight: 32
        color: down.pressed ? palette.highlightColor : palette.transparent

        Image {
            anchors.centerIn: parent
            opacity: enabled ? 1 : 0.5
            source: "qrc:/resources/icons/minus.svg"
        }
    }

    up.indicator: Rectangle {
        x: spinBox.mirrored ? 0 : spinBox.width - width
        height: spinBox.height
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

