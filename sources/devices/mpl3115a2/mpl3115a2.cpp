#include "mpl3115a2.h"

// Std
#include <unistd.h>

// Datasheet http://cdn.sparkfun.com/datasheets/Sensors/Pressure/MPL3115A2.pdf
// Some code copied from Arduio implementation from
// https://github.com/sparkfun/MPL3115A2_Breakout/blob/master/Libraries/Arduino

// Adress
#define MPL3115A2_ADRESS 0x60 // WARNING: 0xC0 in datasheet?

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

void delay(unsigned long ms)
{
    usleep(ms * 1000);
}

using namespace devices;

Mpl3115A2::Mpl3115A2():
    I2cDevice()
{}

bool Mpl3115A2::start()
{
    if (!I2cDevice::start()) return false;
    if (this->i2cRead(WHO_AM_I) != 0xC4) return false;

    return true;
}

int Mpl3115A2::i2cAddress() const
{
    return MPL3115A2_ADRESS;
}

void Mpl3115A2::setPowerMode(PowerMode mode)
{
    uint8_t setting = this->i2cRead(CTRL_REG1);

    switch (mode) {
    case Active:
        setting |= (1 << 0);
        break;
    case Standby:
        setting &= ~(1 << 0);
        break;
    }

    this->i2cWrite(CTRL_REG1, setting);
}

void Mpl3115A2::setMeasurementMode(MeasurementMode mode)
{
    uint8_t setting = this->i2cRead(CTRL_REG1);

    switch (mode) {
    case Active:
        setting |= (1 << 7);
        break;
    case Standby:
        setting &= ~(1 << 7);
        break;
    }

    this->i2cWrite(CTRL_REG1, setting);
}

void Mpl3115A2::enableEventFlags()
{
    this->i2cWrite(PT_DATA_CFG, 0x07); // Enable all three pressure and temp event flags
}

void Mpl3115A2::toggleOneShot()
{
    uint8_t setting = this->i2cRead(CTRL_REG1); //Read current settings
    setting &= ~(1 << 1); //Clear OST bit
    this->i2cWrite(CTRL_REG1, setting);

    setting = this->i2cRead(CTRL_REG1); //Read current settings to be safe
    setting |= (1 << 1); //Set OST bit
    this->i2cWrite(CTRL_REG1, setting);
}

float Mpl3115A2::readAltitude()
{
    this->toggleOneShot();

    float result = 0.0;
    return result;
}

float Mpl3115A2::readPressure()
{
    if ((this->i2cRead(STATUS) & (1 << 2)) == 0) this->toggleOneShot();

    // Wait for PDR bit, indicates we have new pressure data
    while ((this->i2cRead(STATUS) & (1 << 2)) == 0) delay(10);

    float result = 0.0;
    return result;

//    TODO: transmission to base class
    // Read pressure registers
//    Wire.beginTransmission(MPL3115A2_ADDRESS);
//    Wire.write(OUT_P_MSB);  // Address of data to get
//    Wire.endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
//    if (Wire.requestFrom(MPL3115A2_ADDRESS, 3) != 3) { // Request three bytes
//        return -999;
//    }

//    byte msb, csb, lsb;
//    msb = Wire.read();
//    csb = Wire.read();
//    lsb = Wire.read();

//    toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

//    // Pressure comes back as a left shifted 20 bit number
//    long pressure_whole = (long)msb<<16 | (long)csb<<8 | (long)lsb;
//    pressure_whole >>= 6; //Pressure is an 18 bit number with 2 bits of decimal. Get rid of decimal portion.

//    lsb &= B00110000; //Bits 5/4 represent the fractional component
//    lsb >>= 4; //Get it right aligned
//    float pressure_decimal = (float)lsb/4.0; //Turn it into fraction

//    float pressure = (float)pressure_whole + pressure_decimal;

//    return(pressure);
}

float Mpl3115A2::readTemperature()
{
    float result = 0.0;
    return result;
}

