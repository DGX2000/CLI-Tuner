#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <algorithm>
#include <array>

/**
 * @brief A filter that returns the median from a collection of samples.
 *
 * @details This filter is used in determining on which range of frequencies to focus on
 * initially. The autocorrelation method for detecting the fundamental frequency is prone to
 * catch some outliers (harmonics), therefore we put several samples into this filter to reject
 * those outliers.
 *
 * @tparam T Data type.
 * @tparam N Amount of samples to hold in filter.
 */
template<typename T, std::size_t N>
class MedianFilter
{
public:
    T getMedian()
    {
        auto mediumIterator = pastValues.begin();
        std::advance(mediumIterator, N/2);
        std::nth_element(pastValues.begin(), mediumIterator, pastValues.begin());
        
        return pastValues[N/2];
    }

    void update(T sample)
    {
        pastValues[writerIndex] = sample;
        writerIndex = (writerIndex + 1) % N;
    }

private:
    std::array<T, N> pastValues{0};
    std::size_t writerIndex{0};
};


#endif // MEDIANFILTER_H
