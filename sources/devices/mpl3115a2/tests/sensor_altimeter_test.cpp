#include "mpl3115a2.h"

// Qt
#include <QDebug>

int main(int argc, char *argv[])
{
    devices::Mpl3115A2 altimeter;

    altimeter.start();

    altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
    altimeter.enableEventFlags();

    qDebug() << "Measure altitude above sea level in meters";
    altimeter.setModeAltimeter();
    for (int i = 0; i < 15; i++)
    {
        altimeter.processMeasurement();
        qDebug() << "alt:" << altimeter.altitude() <<
                    "tmp:" << altimeter.temperature() <<
                    "prs:" << altimeter.pressure();
    }

    qDebug() << "Measure pressure level in kPa";
    altimeter.setModeBarometer();
    for (int i = 0; i < 15; i++)
    {
        altimeter.processMeasurement();
        qDebug() << "alt:" << altimeter.altitude() <<
                    "tmp:" << altimeter.temperature() <<
                    "prs:" << altimeter.pressure();
    }

    qDebug() << "Measure altitude above sea level in meters";
    altimeter.setModeAltimeter();
    for (int i = 0; i < 15; i++)
    {
        altimeter.processMeasurement();
        qDebug() << "alt:" << altimeter.altitude() <<
                    "tmp:" << altimeter.temperature() <<
                    "prs:" << altimeter.pressure();
    }
    return 0;
}
