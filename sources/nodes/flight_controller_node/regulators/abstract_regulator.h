#ifndef ABSTRACT_REGULATOR_H
#define ABSTRACT_REGULATOR_H

namespace domain
{
    class AbstractRegulator
    {
    public:
        AbstractRegulator(float targetValue, float inputValue);

        float targetValue() const;
        void setTargetValue(float targetValue);

        float inputValue() const;
        void setInputValue(float inputValue);

        float outputValue() const;

        virtual float regulate() = 0;

    protected:
        float m_targetValue;
        float m_inputValue;
        float m_outputValue;
    };
}

#endif // ABSTRACT_REGULATOR_H
