#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <algorithm>
#include <array>

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
