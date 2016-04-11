import QtQuick 2.5
import "/js/helpers/drawer_helper.js" as Helper

Item {
    id: rollScale

    property int roll: 0
    property int minRoll: -35
    property int maxRoll: 35
    property int valueStep: 5

    width: height

    onRollChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');
            Helper.prepareContext(ctx);

            ctx.save();
            ctx.clearRect(0, 0, width, height);
            ctx.textBaseline = 'middle';

            ctx.moveTo(width / 2, height / 2);
            for (var i = minRoll - (minRoll % valueStep); i <= maxRoll;
                 i += (valueStep / 2)) {
                ctx.save();
                ctx.rotate(i * Math.PI / 180);
                ctx.moveTo(0, -height / 2);
                ctx.lineTo(0, -height / 2 + 15);
                ctx.restore();
            }
            ctx.stroke();
            ctx.restore();
        }
    }
}
