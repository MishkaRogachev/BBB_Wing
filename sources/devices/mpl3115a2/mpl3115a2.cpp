#include "mpl3115a2.h"

// Qt TMP:
#include <QDebug>

// Std
#include <unistd.h>

// Adress
#define MPL3115A2_ADRESS 0x60

// Registers
#define STATUS     0x00
#define OUT_P_MSB  0x01
#define OUT_P_CSB  0x02
#define OUT_P_LSB  0x03
#define OUT_T_MSB  0x04
#define OUT_T_LSB  0x05
#define DR_STATUS  0x06
#define OUT_P_DELTA_MSB  0x07
#define OUT_P_DELTA_CSB  0x08
#define OUT_P_DELTA_LSB  0x09
#define OUT_T_DELTA_MSB  0x0A
#define OUT_T_DELTA_LSB  0x0B
#define WHO_AM_I   0x0C
#define F_STATUS   0x0D
#define F_DATA     0x0E
#define F_SETUP    0x0F
#define TIME_DLY   0x10
#define SYSMOD     0x11
#define INT_SOURCE 0x12
#define PT_DATA_CFG 0x13
#define BAR_IN_MSB 0x14
#define BAR_IN_LSB 0x15
#define P_TGT_MSB  0x16
#define P_TGT_LSB  0x17
#define T_TGT      0x18
#define P_WND_MSB  0x19
#define P_WND_LSB  0x1A
#define T_WND      0x1B
#define P_MIN_MSB  0x1C
#define P_MIN_CSB  0x1D
#define P_MIN_LSB  0x1E
#define T_MIN_MSB  0x1F
#define T_MIN_LSB  0x20
#define P_MAX_MSB  0x21
#define P_MAX_CSB  0x22
#define P_MAX_LSB  0x23
#define T_MAX_MSB  0x24
#define T_MAX_LSB  0x25
#define CTRL_REG1  0x26
#define CTRL_REG2  0x27
#define CTRL_REG3  0x28
#define CTRL_REG4  0x29
#define CTRL_REG5  0x2A
#define OFF_P      0x2B
#define OFF_T      0x2C
#define OFF_H      0x2D

using namespace devices;

Mpl3115A2::Mpl3115A2():
    I2cDevice()
{}

bool Mpl3115A2::start(const char* filename)
{
    if (!I2cDevice::start(filename)) return false;
    if (this->i2cRead(WHO_AM_I) != 0xC4) return false;

    return true;
}

uint8_t Mpl3115A2::i2cAddress() const
{
    return MPL3115A2_ADRESS;
}

float Mpl3115A2::readAltitude()
{
    qDebug() << "Enable Data Flags";

    this->i2cWrite(CTRL_REG1, 0xB8); // Set to Altimeter with an OSR = 128
    this->i2cWrite(PT_DATA_CFG, 0x07); // Enable Data Flags in PT_DATA_CFG
    this->i2cWrite(CTRL_REG1, 0xB9); // Set Active (polling)

    qDebug() << "Starting measure";

    for (int counter = 0; counter < 60; ++counter) //Error out after max of 512ms for a read
    {
        uint8_t status = this->i2cRead(STATUS);
        qDebug() << "Status:" << status;

        if ((status & (1<<2)) != 0)
        {
            qDebug() << "Writing ";

            uint8_t msb = this->i2cRead(0x01);
            uint8_t csb = this->i2cRead(0x02);
            uint8_t lsb = this->i2cRead(0x04);

            qDebug() << "Msb:" << msb << "Csb:" << csb << "Lsb:" << lsb;

            float tempcsb = (lsb>>4) / 16.0;
            float altitude = (float)( (msb << 8) | csb) + tempcsb;

            return altitude;
        }

        usleep(10);
    }

    return 0.0;
}
