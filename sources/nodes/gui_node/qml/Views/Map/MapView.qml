import QtQuick 2.5
import QtLocation 5.5
import QtPositioning 5.5
import "../../Controls"

Map {
    id: map

    plugin: Plugin { name: "osm" }
    gesture.activeGestures: MapGestureArea.PanGesture |
                            MapGestureArea.FlickGesture |
                            MapGestureArea.ZoomGesture
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    gesture.onPanStarted: fitButton.checked = false
    MouseArea { // FIXME: touch gestures bug workaround, must be fixed since Qt 5.6
        anchors.fill: parent
    }
    activeMapType: supportedMapTypes[5] // TerrainMapType

    MapPolyline {
        id: track
        line.width: 3
        line.color: "#1abc9c"
    }

    MapQuickItem {
        id: boardMarker
        anchorPoint.x: mark.width / 2
        anchorPoint.y: mark.height / 2
        coordinate: boardService.position
        sourceItem: Item {
            id: mark
            width: 64
            height: 64

            Image {
                anchors.centerIn: parent
                rotation: boardService.yaw
                source: "qrc:/resources/indicators/plane_map_mark.svg"
            }
        }
        onCoordinateChanged: {
            track.addCoordinate(coordinate);
            if (fitButton.checked) map.fitViewportToMapItems()
        }
    }

    Button {
        id: fitButton
        checkable: true
        onCheckedChanged: if (checked) map.fitViewportToMapItems()
        icon: "qrc:/resources/icons/fit.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 15
    }
}
