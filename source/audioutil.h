#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include <cstdint>

/**
 * @brief A helper class for determining the fundamental frequency and volume
 * of an audio signal.
 */
class AudioUtil
{
public:
    /**
     * Struct that contains the values of the recorded audio samples and the amount
     * of samples.
     */
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

    /**
     * @brief Determines the fundamental period length of an audio signal.
     *
     * @details This function approaches the problem of finding the fundamental period length
     * by repeatedly correlating the signal with a shifted version of itself. The shift that
     * causes the maximum correlation is taken to be the fundamental period length.
     *
     * @param signal Signal consisting of samples.
     * @param range Range of period lengths in which to look for the fundamental period length.
     * @return Fundamental period length.
     */
    static PeriodLength detectFundamentalPeriodLength(const Signal& signal, const PeriodLengthRange& range);

    /**
     * @brief Correlates a signal with a shifted version of itself
     * @param signal Signal consisting of samples.
     * @param shift How much to shift the signal for the correlation operation.
     * @return Result of the correlation, i.e. how much the signal resembles the shifted version.
     */
    static double autocorrelation(const Signal& signal, const std::uint64_t shift);

    /**
     * @brief Compute the root-mean-square volume of the signal.
     * @param signal Signal consisting of samples.
     * @return Root-mean-square volume of the signal.
     */
    static double computeRmsVolume(const Signal& signal);

    /**
     * @brief Convert a root-mean-square volume into decibels.
     *
     * @details Decibels are used by the volume display in the terminal as a logarithmic scale
     * is more fit to indicate changes in volume. As reference for the logarithm the maximum
     * value an integer of 16 bits (e.g. a sample) can hold is used (as it is commonly done
     * in digital audio).
     * @param rmsVolume Root-mean-square volume.
     * @return Volume in decibels.
     */
    static double rmsVolumeToDecibels(double rmsVolume);

    /**
     * @brief Convert a period length to a frequency.
     * @param periodLength Period length to be converted.
     * @param samplingRate Sampling rate used by the recorder.
     * @return Frequency in Hz (hertz, 1/s).
     */
    static double periodToFrequency(const double periodLength, const std::uint64_t samplingRate);
};

#endif // AUDIOUTIL_H
