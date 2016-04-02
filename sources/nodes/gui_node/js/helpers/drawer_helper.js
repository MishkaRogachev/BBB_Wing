.pragma library

function prepareContext(ctx) {
    ctx.lineWidth = 2;
    ctx.strokeStyle = '#ecf0f1';
    ctx.fillStyle = '#ecf0f1';
    ctx.font = '11pt Open Sans';
}

function mapToPixel(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}
