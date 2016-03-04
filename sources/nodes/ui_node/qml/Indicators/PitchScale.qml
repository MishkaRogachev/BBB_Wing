import QtQuick 2.5
import "/js/helpers/drawer_helper.js" as Helper

Item {
    id: pitchScale

    property int value: 0
    property int minValue: -20
    property int maxValue: 20
    property int valueStep: 10

    width: 96
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.save();
            context.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = '#ecf0f1';
            ctx.fillStyle = '#ecf0f1';
            ctx.font = '11pt Open Sans';
            ctx.textBaseline = 'middle';

            ctx.beginPath();

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i < maxValue;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                var yPos = Helper.mapToPixel(i, minValue, maxValue, height);

                ctx.moveTo(major ? 24 : 36, yPos);
                ctx.lineTo(major ? width - 24 : width - 36, yPos);

                if (major) {
                    ctx.textAlign = 'right';
                    ctx.fillText(i, 22, yPos);
                    ctx.textAlign = 'left';
                    ctx.fillText(i, width - 22, yPos);
                }
            }

            ctx.stroke();
            ctx.restore();
        }
    }
}
