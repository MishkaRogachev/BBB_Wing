import QtQuick 2.5
import QtGraphicalEffects 1.0

Item {
    id: horizont

    property real pitch: 0.0
    property real roll: 0.0
    property real pitchScale: 2.5
    property alias radius: mask.radius
    property alias skyColor: sky.color
    property alias groundColor: sky.color

    Item {
        id: skyGround
        visible: false
        anchors.fill: parent
        property real size: Math.sqrt(Math.pow(horizont.width, 2) +
                                      Math.pow(horizont.height, 2))

        Column {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -pitch * pitchScale
            rotation: roll

            Rectangle {
                id: sky
                width: skyGround.size * 1.5
                height: skyGround.size * 1.5
                color: "#3498db"
                antialiasing: true
            }

            Rectangle {
                id: ground
                width: skyGround.size * 1.5
                height: skyGround.size * 1.5
                color: "#e67e22"
                antialiasing: true
            }
        }
    }

    OpacityMask {
        anchors.fill: skyGround
        source: skyGround
        maskSource: mask
    }

    Rectangle {
        id: mask
        width: skyGround.width
        height: skyGround.height
        radius: 36
        visible: false
    }
}
