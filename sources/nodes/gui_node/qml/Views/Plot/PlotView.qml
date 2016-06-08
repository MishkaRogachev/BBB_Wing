import QtQuick 2.6
import QtCharts 2.0

ChartView {
    id: plot
    antialiasing: true
    animationOptions: ChartView.SeriesAnimations
    property bool openGL: true
    backgroundRoundness: 0

    property int time: 0

    function formatAngle(angle) {
        if (angle > 180) return angle - 360;
        return angle;
    }

    Timer {
        repeat: true
        interval: 25
        running: true
        onTriggered: time++;
    }

    Connections {
        target: boardService
        onPitchChanged: pitchSeries.append(time, formatAngle(pitch))
        onRollChanged: rollSeries.append(time, formatAngle(roll))
        onYawChanged: yawSeries.append(time, formatAngle(yaw))
        onGroundSpeedChanged: groundSpeedSeries.append(time, groundSpeed)
        onBarAltitudeChanged: barAltitudeSeries.append(time, barAltitude)
    }

    ValueAxis {
        id: timeAxis
        min: 0
        max: time
        tickCount: 5
    }

    ValueAxis {
        id: angleAxis
        min: -180
        max: 180
    }

    ValueAxis {
        id: speedAxis
        min: 0
        max: 100
    }

    ValueAxis {
        id: altitudeAxis
        min: -1000
        max: 10000
    }

    LineSeries {
        name: qsTr("Pitch")
        id: pitchSeries
        axisX: timeAxis
        axisY: angleAxis
    }

    LineSeries {
        name: qsTr("Roll")
        id: rollSeries
        axisX: timeAxis
        axisY: angleAxis
    }

    LineSeries {
        name: qsTr("Yaw")
        id: yawSeries
        axisX: timeAxis
        axisY: angleAxis
    }

    LineSeries {
        name: qsTr("Ground speed")
        id: groundSpeedSeries
        axisX: timeAxis
        axisY: speedAxis
    }

    LineSeries {
        name: qsTr("Barometric altitude")
        id: barAltitudeSeries
        axisX: timeAxis
        axisY: altitudeAxis
    }
}
