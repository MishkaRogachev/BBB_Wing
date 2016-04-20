#include "pca9685.h"
#include "pca9685_registers.h"

using namespace devices;

Pca9685::Pca9685():
    I2cDevice()
{}

bool Pca9685::start(const char* filename)
{
    if (!I2cDevice::start(filename)) return false;

    this->reset();
    this->setFrequency(1000); // to settings

    return true;
}

uint8_t Pca9685::i2cAddress() const
{
    return ALLCALLADR;
}

bool Pca9685::checkDevicePresent()
{
    return true; //TODO: this->i2cRead(WHO_AM_I) == 0xC4;
}

void Pca9685::reset()
{
    this->i2cWrite(MODE1, 0x01); // Normal mode FIXME: check 0x00
    this->i2cWrite(MODE2, 0x04); // Totem pole
}

void Pca9685::setFrequency(float frequency)
{
    uint8_t prescaledFrequency = (CLOCK_FREQ / 4096 / frequency) - 1;
    this->i2cWrite(MODE1, 0x10); // Sleep
    this->i2cWrite(PRE_SCALE, prescaledFrequency); // Multiplyer for PWM frequency
    this->i2cWrite(MODE1, 0x80); // Restart
    this->i2cWrite(MODE2, 0x04); // Totem pole
}

void Pca9685::setPwm(uint8_t channel, int value)
{
    this->setPwm(channel, 0, value);
}

void Pca9685::setPwm(uint8_t channel, int onValue, int offValue)
{
    this->i2cWrite(LED0_ON_L + LED_MULTIPLYER * (channel - 1), onValue & 0xFF);
    this->i2cWrite(LED0_ON_H + LED_MULTIPLYER * (channel - 1), onValue >> 8);
    this->i2cWrite(LED0_OFF_L + LED_MULTIPLYER * (channel - 1), offValue & 0xFF);
    this->i2cWrite(LED0_OFF_H + LED_MULTIPLYER * (channel - 1), offValue >> 8);
}

int Pca9685::pwm(uint8_t channel)
{
    int value = this->i2cRead(LED0_OFF_H + LED_MULTIPLYER * (channel - 1));
    value = value & 0xf;
    value <<= 8;
    value += this->i2cRead(LED0_OFF_L + LED_MULTIPLYER * (channel - 1));
    return value;
}
