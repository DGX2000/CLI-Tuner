#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include <cstdint>


class AudioUtil
{
public:
    struct Signal
    {
        const std::int16_t* samples;
        const std::uint64_t length;
    };

    using PeriodLength = std::uint64_t;
    struct PeriodLengthRange
    {
        PeriodLength min;
        PeriodLength max;
    };

public:
    AudioUtil() = delete;

    static PeriodLength detectFundamentalPeriodLength(const Signal& signal, const PeriodLengthRange& range);
    static double autocorrelation(const Signal& signal, const std::uint64_t shift);

    static double computeRmsVolume(const Signal& signal);
    static double rmsVolumeToDecibels(double rmsVolume);

    static double periodToFrequency(const double periodLength, const std::uint64_t samplingRate);
};

#endif // AUDIOUTIL_H
