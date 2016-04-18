import QtQuick 2.5
import QtMultimedia 5.5

Rectangle {
    id: video

    color: "black"

    VideoOutput {
        id: videoOutput
        source: videoService
        anchors.fill: parent
    }
}
