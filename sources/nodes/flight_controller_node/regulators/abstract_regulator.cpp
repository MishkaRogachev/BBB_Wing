#include "abstract_regulator.h"

using namespace domain;

AbstractRegulator::AbstractRegulator(float targetValue):
    m_targetValue(targetValue),
    m_outputValue(0.0)
{}

float AbstractRegulator::targetValue() const
{
    return m_targetValue;
}

void AbstractRegulator::setTargetValue(float targetValue)
{
    m_targetValue = targetValue;
}

float AbstractRegulator::outputValue() const
{
    return m_outputValue;
}
