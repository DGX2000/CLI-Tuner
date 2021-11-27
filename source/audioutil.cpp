#include "audioutil.h"

#include <cmath>
#include <limits>
#include <vector>

AudioUtil::PeriodLength AudioUtil::detectFundamentalPeriodLength(const Signal &signal, const PeriodLengthRange &range)
{
    double maxAutocorrelation{0.0};
    PeriodLength maxPeriodLength{range.min};

    for(auto shift = range.min; shift < range.max; ++shift)
    {
        auto currentAutocorrelation = autocorrelation(signal, shift);

        if(currentAutocorrelation > maxAutocorrelation)
        {
            maxPeriodLength = shift;
            maxAutocorrelation = currentAutocorrelation;
        }
    }

    return maxPeriodLength;
}

double AudioUtil::autocorrelation(const Signal &signal, const uint64_t shift)
{
    double result = 0.0;

    for(auto i = shift; i < signal.length; ++i)
    {
        result += signal.samples[i] * signal.samples[i - shift];
    }

    return result / static_cast<double>(signal.length - shift);
}

double AudioUtil::computeRmsVolume(const Signal &signal)
{
    auto volume = double{0.0};

    for(std::uint64_t i = 0; i < signal.length; ++i)
    {
        volume += signal.samples[i] * signal.samples[i];
    }

    return std::sqrt(volume / static_cast<double>(signal.length));
}

double AudioUtil::rmsVolumeToDecibels(double rmsVolume)
{
    return 10.0 * std::log10(rmsVolume / static_cast<double>(std::numeric_limits<std::int16_t>::max()));
}

double AudioUtil::periodToFrequency(const double periodLength, const uint64_t samplingRate)
{
    return static_cast<double>(samplingRate) / static_cast<double>(periodLength);
}
