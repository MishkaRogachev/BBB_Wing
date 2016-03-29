import QtQuick 2.5
import QtMultimedia 5.5

Rectangle {
    id: video

    color: "black"

    Camera { // TODO: impliment presenter for device/file video source
        id: camera
        deviceId: QtMultimedia.availableCameras[QtMultimedia.availableCameras.length - 1].deviceId
    }

    VideoOutput {
        id: videoOutput
        source: camera
        anchors.fill: parent
    }
}
