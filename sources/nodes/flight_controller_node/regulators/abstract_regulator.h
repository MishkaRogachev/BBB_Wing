#ifndef ABSTRACT_REGULATOR_H
#define ABSTRACT_REGULATOR_H

namespace domain
{
    class AbstractRegulator
    {
    public:
        AbstractRegulator(float targetValue);

        float targetValue() const;
        void setTargetValue(float targetValue);

        float outputValue() const;

        virtual float regulate(float inputValue) = 0;

    protected:
        float m_targetValue;
        float m_outputValue;
    };
}

#endif // ABSTRACT_REGULATOR_H
