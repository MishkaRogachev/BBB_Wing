import QtQuick 2.0
import QtLocation 5.3

Item {
    id: map

    Map {
        id: mapCanvas
        anchors.fill: parent
        plugin: Plugin {
            preferred: ["osm"] // TODO: offline maps
        }
    }
}
