import QtQuick 2.6
import Qt.labs.controls 1.0
import "./" as Current
import "qrc:/js/helper.js" as Helper

Control {
    id: control

    property real value: 0
    property real stepSize: 0.001
    property bool longitude: false

    implicitWidth: Math.max(background.implicitWidth,
                            contentItem.implicitWidth +
                            2 * padding +
                            up.implicitWidth +
                            down.implicitWidth)
    implicitHeight: 32
    font.pointSize: 11
    padding: 6
    leftPadding: -(up.width + down.width) / 2
    rightPadding: 6 + control.mirrored ? down.width : up.width

    background: Rectangle {
        implicitWidth: 32
        implicitHeight: 32
        color: palette.backgroundColor
    }

    contentItem: TextInput {
        text: Helper.degreesToDmsString(value, longitude)
        onEditingFinished: value =  Helper.dmsStringToDegree(text, longitude)
        font: control.font
        color: palette.textColor
        selectionColor: palette.highlightColor
        selectedTextColor: color
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        validator: RegExpValidator {
            regExp: /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/
        }
    }

    Current.Button {
        id: down
        x: control.mirrored ? up.width : control.width - width - up.width
        height: control.height
        width: height
        backgroundColor: pressed ? palette.highlightColor : palette.transparent
        icon: "qrc:/resources/icons/minus.svg"
        onClicked: value -= stepSize
        autoRepeat: true
    }

    Current.Button {
        id: up
        x: control.mirrored ? 0 : control.width - width
        height: control.height
        width: height
        backgroundColor: pressed ? palette.highlightColor : palette.transparent
        icon: "qrc:/resources/icons/plus.svg"
        onClicked: value += stepSize
        autoRepeat: true
    }
}
