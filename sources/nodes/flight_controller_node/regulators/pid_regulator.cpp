#include "pid_regulator.h"

// Qt
#include <QtGlobal>

using namespace domain;

PidRegulator::PidRegulator(float proportional, float integral, float derivative,
                           float lowerBound, float upperBound,
                           float errorThreshold, float targetValue):
    m_proportional(proportional),
    m_integral(integral),
    m_derivative(derivative),
    m_lowerBound(lowerBound),
    m_upperBound(upperBound),
    m_errorThreshold(errorThreshold),
    m_targetValue(targetValue),
    m_outputValue(0.0),
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

float PidRegulator::targetValue() const
{
    return m_targetValue;
}

void PidRegulator::setTargetValue(float targetValue)
{
    m_targetValue = targetValue;
}

float PidRegulator::regulate(float inputValue, float frequency)
{
    float errorValue = m_targetValue - inputValue;

    if (qAbs(errorValue) > m_errorThreshold)
    {
        m_outputValue = m_proportional * errorValue +
                        m_integral * m_integralValue / frequency +
                        m_derivative * (errorValue - m_outputValue) * frequency;

        if (m_outputValue > m_upperBound) m_outputValue = m_upperBound;
        if (m_outputValue < m_lowerBound) m_outputValue = m_lowerBound;

        m_integralValue += (errorValue + m_lastErrorValue) / 2;
        m_lastErrorValue = errorValue;
    }

    return m_outputValue;
}


