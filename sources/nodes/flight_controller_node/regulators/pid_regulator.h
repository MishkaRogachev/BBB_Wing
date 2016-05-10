#ifndef PID_REGULATOR_H
#define PID_REGULATOR_H

#include "abstract_regulator.h"

namespace domain
{
    class PidRegulator: public AbstractRegulator
    {
    public:
        PidRegulator(float proportional, float integral, float derivative,
                     float lowerBound, float upperBound, float errorThreshold = 0.0,
                     float frequency = 1.0, float targetValue = 0.0);

        float proportional() const;
        void setProportional(float proportional);

        float integral() const;
        void setIntegral(float integral);

        float derivative() const;
        void setDerivative(float derivative);

        float upperBound() const;
        void setUpperBound(float upperBound);

        float lowerBound() const;
        void setLowerBound(float lowerBound);

        float errorThreshold() const;
        void setErrorThreshold(float errorThreshold);

        float frequency() const;
        void setFrequency(float frequency);

        float targetValue() const;
        void setTargetValue(float targetValue);

        float regulate(float inputValue) override;

    private:
        float m_proportional;
        float m_integral;
        float m_derivative;
        float m_lowerBound;
        float m_upperBound;
        float m_errorThreshold;
        float m_frequency;
        float m_integralValue;
        float m_lastErrorValue;
    };
}

#endif // PID_REGULATOR_H
