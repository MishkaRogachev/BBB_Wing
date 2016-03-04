import QtQuick 2.5

Clickable {
    id: button

    property bool checkable: false
    property bool checked: false

    Rectangle {
        anchors.fill: parent
        color: checked ? "#16a085" : "#34495e"
        z: -1
    }

    onClicked: if (checkable) checked = !checked
}
