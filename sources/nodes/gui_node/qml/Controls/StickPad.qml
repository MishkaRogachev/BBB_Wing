import QtQuick 2.0

Row {
    id: stickPad

    signal deviationChanged(int channel, real deviation);
    property alias model: repeater.model

    Repeater {
        id: repeater
        model: 2

        Stick {
            width: stickPad.height - stickPad.spacing
            onDeviationXChanged: deviationChanged(index * 2, deviationX)
            onDeviationYChanged: deviationChanged(index * 2 + 1, deviationY)
        }
    }
}
