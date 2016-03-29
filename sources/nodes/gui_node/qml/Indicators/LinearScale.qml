import QtQuick 2.0
import "/js/helpers/drawer_helper.js" as Helper

Item {
    id: scale

    property int value: 0
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20
    property alias canvasRotation: canvas.rotation

    property bool vertical: (canvasRotation >=90 && canvasRotation < 180) ||
                            (canvasRotation <= -90 && canvasRotation > -180)

    width: 96
    height: 64
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: vertical ? parent.height : parent.width
        height: vertical ? parent.width : parent.height
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.save();
            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = '#ecf0f1';
            ctx.fillStyle = '#ecf0f1';

            ctx.beginPath();

            ctx.font = '11pt Open Sans';
            ctx.textAlign = vertical ?
                        (canvasRotation > 0 ? 'left' :'right') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'bottom';

            ctx.moveTo(0, height / 2);
            ctx.lineTo(width, height / 2);

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i < maxValue;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                var xPos = canvasRotation > 0 ?
                            width - Helper.mapToPixel(i, minValue, maxValue, width) :
                            Helper.mapToPixel(i, minValue, maxValue, width);
                ctx.moveTo(xPos, height / 2);
                ctx.lineTo(xPos, height / 2 - (major ? 8 : 6));
                if (major) {
                    ctx.save();
                    ctx.translate(xPos, height / 2 - 8);
                    ctx.rotate(-canvasRotation * Math.PI / 180);
                    ctx.fillText(i, 0, 2);
                    ctx.restore();
                }
            }

            ctx.moveTo(width / 2 - 10, height / 2 + 8);
            ctx.lineTo(width / 2, height / 2 + 2);
            ctx.lineTo(width / 2 + 10, height / 2 + 8);

            ctx.font = '14pt Open Sans';
            ctx.textAlign = vertical ?
                        (canvasRotation < 0 ? 'left' :'right') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';
            ctx.save();
            ctx.translate(width / 2, height / 2 + (vertical ? 8 : 2));
            ctx.rotate(-canvasRotation * Math.PI / 180);
            ctx.fillText(value, 0, 2);
            ctx.restore();

            ctx.stroke();
            ctx.restore();
        }
    }
}
