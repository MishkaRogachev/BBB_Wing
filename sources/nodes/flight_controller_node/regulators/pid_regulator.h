#ifndef PID_REGULATOR_H
#define PID_REGULATOR_H

namespace domain
{
    class PidRegulator
    {
    public:
        PidRegulator(float proportional, float integral, float derivative,
                     float lowerBound, float upperBound,
                     float errorThreshold = 0.0, float targetValue = 0.0);

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

        float targetValue() const;
        void setTargetValue(float targetValue);

        float regulate(float inputValue, float frequency);

    private:
        float m_proportional;
        float m_integral;
        float m_derivative;
        float m_lowerBound;
        float m_upperBound;
        float m_errorThreshold;
        float m_targetValue;
        float m_outputValue;
        float m_integralValue;
        float m_lastErrorValue;
    };
}

#endif // PID_REGULATOR_H
