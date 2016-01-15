#include "mpl3115a2.h"

// Qt
#include <QDebug>

int main(int argc, char *argv[])
{
    devices::Mpl3115A2 altimeter;

    altimeter.start();

    altimeter.setModeAltimeter(); // Measure altitude above sea level in meters

    altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
    altimeter.enableEventFlags();

    qDebug() << "Pressure:" << altimeter.readAltitude();
/*    qDebug() << "Altitude:" << altimeter.readAltitude();
    qDebug() << "Temperature:" << altimeter.readTemperature();
*/
    return 0;
}
