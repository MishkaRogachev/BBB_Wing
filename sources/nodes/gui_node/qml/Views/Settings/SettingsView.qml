import QtQuick 2.5
import "../../Controls"

Rectangle {
    color: palette.backgroundColor

    Column {
        anchors.left: parent.left
        anchors.top: parent.top

        Repeater {
            model: [ { name: qsTr("Gui"), source: "GuiSettings.qml" } ]

            Clickable {
                text: modelData.name
            }
        }
    }
}
