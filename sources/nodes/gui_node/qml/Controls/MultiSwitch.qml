import QtQuick 2.5

Row {
    id: multiSwitch

    property alias model: repeater.model
    property variant selectedItem: repeater.model[selectedItemIndex]
    property int selectedItemIndex: -1

    Repeater {
        id: repeater
        model : [ { text:qsTr("ON") }, { text:qsTr("OFF") } ]

        Button {
            width: multiSwitch.width / repeater.count
            text: modelData.text ? modelData.text : ""
            icon: modelData.icon ? modelData.icon : ""
            onClicked: selectedItemIndex = index
            checked: selectedItemIndex == index
        }
    }
    Component.onCompleted: selectedItemIndex = 0
}
