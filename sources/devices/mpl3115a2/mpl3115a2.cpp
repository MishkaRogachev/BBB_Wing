#include "mpl3115a2.h"
#include "mpl3115a2_registers.h"

// Std
#include <unistd.h>
#include <limits>

// Implimentation based on Sparkfun's Arduino libary code
// https://github.com/sparkfun/MPL3115A2_Breakout/tree/V_H1.1_L1.2.0/Libraries/Arduino/src
// They said code is beerware!

using namespace devices;

Mpl3115A2::Mpl3115A2(const char* filename):
    I2cDevice(filename),
    m_altitude(std::numeric_limits<float>::quiet_NaN()),
    m_temperature(std::numeric_limits<float>::quiet_NaN()),
    m_pressure(std::numeric_limits<float>::quiet_NaN())
{}

bool Mpl3115A2::start()
{
    if (!I2cDevice::start()) return false;

    // Set Oversample to the recommended 128
    this->setOversampleRate(7);
    this->enableEventFlags();
    this->setModeAltimeter();

    return true;
}

uint8_t Mpl3115A2::i2cAddress() const
{
    return MPL3115A2_ADRESS;
}

bool Mpl3115A2::checkDevicePresent()
{
    return this->i2cRead(WHO_AM_I) == 0xC4;
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

    int8_t t_msb = this->i2cRead(OUT_T_MSB);
    int8_t t_lsb = this->i2cRead(OUT_T_LSB);

    float templsb = (t_lsb >> 4) / 16.0;
    m_temperature = (float)(t_msb + templsb);
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
