#ifndef RUNNINGAVERAGEFILTER_H
#define RUNNINGAVERAGEFILTER_H

#include <cstdint>

template<typename T>
class RunningAverageFilter
{
public:
    double getMean() const
    {
        return mean;
    }

    void reset()
    {
        numberOfSamples = 0;
        mean = 0.0;
    }

    void update(T sample)
    {
        ++numberOfSamples;
        mean += (sample - mean) / numberOfSamples;
    }

private:
    std::uint64_t numberOfSamples{0};
    T mean{0.0};
};

#endif // RUNNINGAVERAGEFILTER_H
