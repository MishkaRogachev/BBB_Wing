import QtQuick 2.5

Clickable {
    id: button

    property bool checkable: false
    property bool checked: false

    Rectangle {
        anchors.fill: parent
        color: checked ? palette.highlightColor : palette.foregroundColor
        Behavior on color { ColorAnimation { duration: 250 } }
        z: -1
    }

    onClicked: if (checkable) checked = !checked
}
