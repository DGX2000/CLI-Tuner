#ifndef RUNNINGAVERAGEFILTER_H
#define RUNNINGAVERAGEFILTER_H

#include <cstdint>

// TODO: Make generic

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

    void update(double sample)
    {
        ++numberOfSamples;
        mean += (sample - mean) / numberOfSamples;
    }

private:
    std::uint64_t numberOfSamples{0};
    double mean{0.0};
};

#endif // RUNNINGAVERAGEFILTER_H
