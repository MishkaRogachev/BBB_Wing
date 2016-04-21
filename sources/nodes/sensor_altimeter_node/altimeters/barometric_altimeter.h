#ifndef BAROMETRIC_ALTIMETER_H
#define BAROMETRIC_ALTIMETER_H

namespace devices
{
    class BarometricAltimeter
    {
    public:
        virtual ~BarometricAltimeter() {}

        virtual void init() = 0;
        virtual bool takeMeasure() = 0;

        virtual float altitude() const = 0;
        virtual float temperature() const = 0;
        virtual float pressure() const = 0;
    };
}

#endif // BAROMETRIC_ALTIMETER_H
