#include "mpl3115a2.h"

// Std
#include <unistd.h>
#include <limits>

// Qt
#include <QDebug>

// Implimentation based on Sparkfun's Arduino libary code
// https://github.com/sparkfun/MPL3115A2_Breakout/tree/V_H1.1_L1.2.0/Libraries/Arduino/src
// They said code is beerware!

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
    I2cDevice(),
    m_altitude(std::numeric_limits<float>::quiet_NaN()),
    m_temperature(std::numeric_limits<float>::quiet_NaN()),
    m_pressure(std::numeric_limits<float>::quiet_NaN())
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

void Mpl3115A2::setModeActive()
{
    this->setRegisterBit(CTRL_REG1, 0); //Set SBYB bit
}

void Mpl3115A2::setModeStandby()
{
    this->clearRegisterBit(CTRL_REG1, 0); //Clear SBYB bit
}

void Mpl3115A2::setModeAltimeter()
{
    this->setRegisterBit(CTRL_REG1, 7); //Set ALT bit
}

void Mpl3115A2::setModeBarometer()
{
    this->clearRegisterBit(CTRL_REG1, 7); //Clear ALT bit
}

void Mpl3115A2::setOversampleRate(int rate)
{
    if(rate > 7) rate = 7; //OS cannot be larger than 0b.0111
    rate <<= 3; //Align it for the CTRL_REG1 register

    uint8_t reg = this->i2cRead(CTRL_REG1); //Read current settings
    reg &= 0b11000111; //Clear out old OS bits
    reg |= rate; //Mask in new OS bits
    this->i2cWrite(CTRL_REG1, reg);
}

void Mpl3115A2::enableEventFlags()
{
    this->i2cWrite(PT_DATA_CFG, 0x07);
}

void Mpl3115A2::toggleOneShot()
{
    this->clearRegisterBit(CTRL_REG1, 1); //Clear OST bit
    this->setRegisterBit(CTRL_REG1, 1); //Set OST bit
}

void Mpl3115A2::processMeasurement()
{
    this->toggleOneShot();

    if (!(this->i2cRead(STATUS) & (1 << 1))) return;

    uint8_t msb = this->i2cRead(OUT_P_MSB);
    uint8_t csb = this->i2cRead(OUT_P_CSB);
    uint8_t lsb = this->i2cRead(OUT_P_LSB);

    if (this->i2cRead(CTRL_REG1) & (1 << 7))
    {
        float templsb = (lsb >> 4) / 16.0;
        m_altitude = (float)((msb << 8) | csb) + templsb;
    }
    else
    {
        float templsb = (lsb >> 4) / 4.0;
        m_pressure = (float)((msb << 8) | csb) + templsb;
    }

    msb = this->i2cRead(OUT_T_MSB);
    lsb = this->i2cRead(OUT_T_LSB);

    float templsb = (lsb >> 4) / 16.0;

    if (msb > 0x7F) msb = 0XFF - msb;
    m_temperature = (float)(msb + templsb);
}

float Mpl3115A2::altitude() const
{
    return m_altitude;
}

float Mpl3115A2::temperature() const
{
    return m_temperature;
}

float Mpl3115A2::pressure() const
{
    return m_pressure;
}
