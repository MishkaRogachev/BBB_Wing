#ifndef I_BAROMETRIC_ALTIMETER_H
#define I_BAROMETRIC_ALTIMETER_H

namespace devices
{
    class IBarometricAltimeter
    {
    public:
        virtual ~IBarometricAltimeter() {}

        virtual void init() = 0;
        virtual bool takeMeasure() = 0;

        virtual float altitude() const = 0;
        virtual float temperature() const = 0;
        virtual float pressure() const = 0;
    };
}

#endif // I_BAROMETRIC_ALTIMETER_H
