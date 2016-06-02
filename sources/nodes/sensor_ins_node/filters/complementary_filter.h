#ifndef COMPLEMENTARY_FILTER_H
#define COMPLEMENTARY_FILTER_H

namespace domain
{
    class ComplementaryFilter
    {
    public:
        ComplementaryFilter();
        ~ComplementaryFilter();

        void setGyroData(float gx, float gy, float gz);
        void setAccelData(float ax, float ay, float az);
        void setMagData(float mx, float my, float mz);

        void process(float dt);
        void reset();

        float pitch() const;
        float roll() const;
        float yaw() const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // COMPLEMENTARY_FILTER_H
