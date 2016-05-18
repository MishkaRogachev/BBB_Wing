.pragma library

function mapToRange(value, minValue, maxValue, length) {
    return (value - minValue) / (maxValue - minValue) * length;
}

function pad(num, size) {
    var str = num.toString();
    while (str.length < size) str = "0" + str;
    return str;
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

function dmsToDegree(deg, min, sec) {
    return deg + min / 60.0 + sec / 3600.0;
}

function degreesToDmsString(degrees) {
    var dms = degreesToDms(degrees);
    return pad(dms.deg, 3) + "\u00B0" +
           pad(dms.min, 2) + "\'" +
           pad(dms.sec.toFixed(2), 5) + "\""
}

function dmsStringToDegree(string) {
    var split = string.split("\u00B0");
    if (split.cout < 2) return 0.0;
    var deg = split[0];
    split = split[1].split("\'");
    if (split.cout < 2) return 0.0;
    var min = split[0];
    var sec = split[1];
    return dmsToDegree(parseInt(deg), parseInt(min), parseFloat(sec));
}
