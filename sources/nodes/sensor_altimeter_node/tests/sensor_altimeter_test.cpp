#include "mpl3115a2.h"

// Qt
#include <QDebug>

int main(int argc, char *argv[])
{
    devices::Mpl3115A2 altimeter;

    altimeter.start();

    qDebug() << "Pressure:" << altimeter.readPressure();
    qDebug() << "Altitude:" << altimeter.readAltitude();
    qDebug() << "Temperature:" << altimeter.readTemperature();

    return 0;
}
