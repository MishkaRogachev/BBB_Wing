import QtQuick 2.5

Item {
    id: planeMark

    property real pitch: 0.0
    property real roll: 0.0
    property real pitchScale: 2.5

    Image {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: pitch * pitchScale
        rotation: roll
        source: "qrc:/resources/indicators/plane_horizont_mark.svg"
    }
}
