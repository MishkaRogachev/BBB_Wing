#ifndef I_IMU_H
#define I_IMU_H

namespace devices
{
    class IImu
    {
    public:
        virtual ~IImu() {}

        virtual void init() = 0;
        virtual bool checkAvalible() = 0;

        virtual float readGyroX() = 0;
        virtual float readGyroY() = 0;
        virtual float readGyroZ() = 0;

        virtual float readAccelX() = 0;
        virtual float readAccelY() = 0;
        virtual float readAccelZ() = 0;

        virtual float readMagX() = 0;
        virtual float readMagY() = 0;
        virtual float readMagZ() = 0;
    };
}

#endif // I_IMU_H
