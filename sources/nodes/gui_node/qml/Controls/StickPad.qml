import QtQuick 2.5

Row {
    id: stickPad

    signal deviationChanged(int channel, real deviation);
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
            onDeviationXChanged: deviationChanged(index * 2, deviationX)
            onDeviationYChanged: deviationChanged(index * 2 + 1, deviationY)
        }
    }
}
