import QtQuick 2.5

Row {
    id: stickPad

    signal deviationChanged(string channel, real deviation);
    property alias model: repeater.model

    Repeater {
        id: repeater

        Stick {
            minX: modelData.minX
            maxX: modelData.maxX
            minY: modelData.minY
            maxY: modelData.maxY
            returningX: modelData.returningX
            returningY: modelData.returningY
            width: stickPad.height - stickPad.spacing
            onDeviationXChanged: deviationChanged(modelData.channelX, deviationX)
            onDeviationYChanged: deviationChanged(modelData.channelY, deviationY)
        }
    }
}
