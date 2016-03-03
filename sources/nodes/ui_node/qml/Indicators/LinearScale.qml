import QtQuick 2.0

Item {
    id: scale

    property int value: 0
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20
    property alias contentsRotation: canvas.rotation

    height: 64
    onValueChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        onPaint:{
            var ctx = canvas.getContext('2d');

            ctx.save();
            context.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = '#ecf0f1';
            ctx.fillStyle = '#ecf0f1';

            ctx.font = '14pt Open Sans';
            ctx.textAlign = 'center';
            ctx.textBaseline = 'bottom';
            ctx.fillText(value, width / 2, height / 2 - 8);

            ctx.beginPath();
            ctx.moveTo(width / 2 - 8, height / 2 - 10);
            ctx.lineTo(width / 2, height / 2 - 2);
            ctx.lineTo(width / 2 + 8, height / 2 - 10);

            ctx.moveTo(0, height / 2);
            ctx.lineTo(width, height / 2);

            ctx.stroke();

            ctx.font = '11pt Open Sans';
            ctx.textAlign = 'center';
            ctx.textBaseline = 'top';

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i < maxValue;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                ctx.moveTo(mapToPixel(i), height / 2);
                ctx.lineTo(mapToPixel(i), height / 2 + (major ? 8 : 6));
                if (major) ctx.fillText(i, mapToPixel(i), height / 2 + 8);
            }

            ctx.stroke();
            ctx.restore();
        }

        function mapToPixel(val) {
            return (val - minValue) / (maxValue - minValue) * width ;
        }
    }
}
