#include "pid_regulator.h"

// Qt
#include <QtGlobal>

using namespace domain;

PidRegulator::PidRegulator(float proportional, float integral, float derivative,
                           float lowerBound, float upperBound, float errorThreshold,
                           float frequency, float targetValue, float inputValue):
    AbstractRegulator(targetValue, inputValue),
    m_proportional(proportional),
    m_integral(integral),
    m_derivative(derivative),
    m_lowerBound(lowerBound),
    m_upperBound(upperBound),
    m_errorThreshold(errorThreshold),
    m_frequency(frequency),
    m_integralValue(0.0),
    m_lastErrorValue(0.0)
{}

float PidRegulator::proportional() const
{
    return m_proportional;
}

void PidRegulator::setProportional(float proportional)
{
    m_proportional = proportional;
}

float PidRegulator::integral() const
{
    return m_integral;
}

void PidRegulator::setIntegral(float integral)
{
    m_integral = integral;
}

float PidRegulator::derivative() const
{
    return m_derivative;
}

void PidRegulator::setDerivative(float derivative)
{
    m_derivative = derivative;
}

float PidRegulator::lowerBound() const
{
    return m_lowerBound;
}

void PidRegulator::setLowerBound(float lowerBound)
{
    m_lowerBound = lowerBound;
}

float PidRegulator::upperBound() const
{
    return m_upperBound;
}

void PidRegulator::setUpperBound(float upperBound)
{
    m_upperBound = upperBound;
}

float PidRegulator::errorThreshold() const
{
    return m_errorThreshold;
}

void PidRegulator::setErrorThreshold(float errorThreshold)
{
    m_errorThreshold = errorThreshold;
}

float PidRegulator::frequency() const
{
    return m_frequency;
}

void PidRegulator::setFrequency(float frequency)
{
    m_frequency = frequency;
}

float PidRegulator::regulate()
{
    float errorValue = m_targetValue - m_inputValue;

    if (qAbs(errorValue) > m_errorThreshold)
    {
        m_outputValue = m_proportional * errorValue +
                        m_integral * m_integralValue / m_frequency +
                        m_derivative * (errorValue - m_outputValue) * m_frequency;

        if (m_outputValue > m_upperBound) m_outputValue = m_upperBound;
        if (m_outputValue < m_lowerBound) m_outputValue = m_lowerBound;

        m_integralValue += (errorValue + m_lastErrorValue) / 2;
        m_lastErrorValue = errorValue;
    }

    return m_outputValue;
}
