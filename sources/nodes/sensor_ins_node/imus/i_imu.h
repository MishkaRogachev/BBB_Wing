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

        // TODO: IMU interface
    };
}

#endif // I_IMU_H
