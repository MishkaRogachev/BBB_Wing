.pragma library

function mapToPixel(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}
