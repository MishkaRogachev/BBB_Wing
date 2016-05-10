#include "abstract_regulator.h"

using namespace domain;

AbstractRegulator::AbstractRegulator(float targetValue, float inputValue):
    m_targetValue(targetValue),
    m_inputValue(inputValue),
    m_outputValue(0.0)
{}

float AbstractRegulator::targetValue() const
{
    return m_targetValue;
}

float AbstractRegulator::inputValue() const
{
    return m_inputValue;
}

void AbstractRegulator::setInputValue(float inputValue)
{
    m_inputValue = inputValue;
}

void AbstractRegulator::setTargetValue(float targetValue)
{
    m_targetValue = targetValue;
}

float AbstractRegulator::outputValue() const
{
    return m_outputValue;
}
