import QtQuick 2.5
import QtLocation 5.5
import QtPositioning 5.5
import "../Controls"

Map {
    id: map
    plugin: Plugin {
        name: "osm"
    }
    gesture.activeGestures: MapGestureArea.PanGesture |
                            MapGestureArea.FlickGesture |
                            MapGestureArea.ZoomGesture
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType

    MapQuickItem {
        id: boardMarker
        anchorPoint.x: image.width / 2
        anchorPoint.y: image.height
        coordinate: QtPositioning.coordinate(boardService.latitude,
                                             boardService.longitude)
        sourceItem: Image {
            id: image
            rotation: boardService.yaw
            source: "qrc:/resources/indicators/plane_map_mark.svg"
        }
    }

    Button {
        icon: "qrc:/resources/icons/fit.svg"
        onClicked: map.fitViewportToMapItems()
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 15
    }
}
