import QtQuick 2.5
import "qrc:/js/helpers/drawer_helper.js" as Helper

Item {
    id: planeMark

    property int pitch: 0
    property int roll: 0

    onRollChanged: canvas.requestPaint()
    onPitchChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');
            var offset = Helper.mapToPixel(pitch, minPitch, maxPitch, height);

            ctx.lineWidth = 4;
            ctx.strokeStyle = palette.backgroundColor;

            ctx.save();
            ctx.translate(width / 2, height / 2);
            ctx.rotate(-roll * Math.PI / 180);
            ctx.translate(0, offset - height / 2);

            ctx.moveTo(-width / 9 * 4, 0);
            ctx.lineTo(-width / 5, 0);
            ctx.lineTo(-width / 10, width / 10);
            ctx.lineTo(0, 0);
            ctx.lineTo(width / 10, width / 10);
            ctx.lineTo(width / 5, 0);
            ctx.lineTo(width / 9 * 4, 0);

            ctx.stroke();
            ctx.restore();
        }
    }
}
