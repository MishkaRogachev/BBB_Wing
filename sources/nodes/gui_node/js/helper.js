.pragma library

function mapToRange(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}

function degreesToDms(degrees) {
    var deg = degrees | 0;
    var frac = Math.abs(degrees - deg);
    var min = (frac * 60) | 0;
    var sec = frac * 3600 - min * 60;

    return {
        deg: deg,
        min: min,
        sec: sec
    }
}

function pad(num, size) {
    var str = num.toString();
    while (str.length < size) str = "0" + str;
    return str;
}

function degreesToDmsString(degrees) {
    var dms = degreesToDms(degrees);
    return pad(dms.deg, 2) + "\u00B0" +
           pad(dms.min, 2) + "\'" +
           pad(dms.sec.toFixed(2), 5) + "\""
}
