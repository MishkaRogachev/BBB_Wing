import QtQuick 2.5
import QtLocation 5.5
import QtPositioning 5.5

Map {
    id: map
    anchors.fill: parent
    plugin: Plugin {
        name: "osm"
    }
    gesture.activeGestures: MapGestureArea.PanGesture |
                            MapGestureArea.FlickGesture |
                            MapGestureArea.ZoomGesture
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType
}
