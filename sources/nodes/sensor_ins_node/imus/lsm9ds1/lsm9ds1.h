#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "i_imu.h"

// Qt
#include <QString>

namespace devices
{
    class Lsm9ds1: public IImu
    {
        class GyroAccel;
        class Mag;

    public:
        Lsm9ds1(const QString& filename);
        ~Lsm9ds1();

        bool start();
        void stop();
        bool isStarted() const;
        bool checkDevicePresent();

        GyroAccel* gyroAccel() const;
        Mag* mag() const;

        void init() override;

        float readGyroX() override;
        float readGyroY() override;
        float readGyroZ() override;

        float readAccelX() override;
        float readAccelY() override;
        float readAccelZ() override;

        float readMagX() override;
        float readMagY() override;
        float readMagZ() override;

    private:
        GyroAccel* m_gyroAccel;
        Mag* m_mag;
    };
}

#endif // LSM9DS1_H
