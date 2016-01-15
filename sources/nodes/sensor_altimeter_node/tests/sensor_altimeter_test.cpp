#include "mpl3115a2.h"

// Qt
#include <QDebug>

int main(int argc, char *argv[])
{
    devices::Mpl3115A2 altimeter;

    altimeter.start();
    altimeter.setModeActive();
    altimeter.setModeAltimeter();

    qDebug() << "Pressure:" << altimeter.readAltitude();
/*    qDebug() << "Altitude:" << altimeter.readAltitude();
    qDebug() << "Temperature:" << altimeter.readTemperature();
*/
    return 0;
}
