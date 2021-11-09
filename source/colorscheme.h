#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Color.hpp>

namespace COLORS
{
sf::Color BACKGROUND = sf::Color(0, 59, 70);
sf::Color OUTLINE = sf::Color(255, 184, 116);
sf::Color OPTIONS = sf::Color(0, 207, 246);
sf::Color SLIDING_BAND = sf::Color(255, 124, 0);
sf::Color SLIDING_BAND_WINDOW = sf::Color(139, 155, 180);

sf::Color TEXT = sf::Color(255, 255, 255);

sf::Color ACCENT = sf::Color(44, 232, 245);
sf::Color ACCENT_TRANSLUCENT = sf::Color(44, 232, 245, 64);
sf::Color TRANSPARENT = sf::Color(0, 0, 0, 0);

sf::Color NO_VOLUME = sf::Color(139, 155, 180);
sf::Color LOW_VOLUME = sf::Color(62, 137, 72);
sf::Color MID_VOLUME = sf::Color(254, 174, 52);
sf::Color HIGH_VOLUME = sf::Color(228, 59, 68);

sf::Color fromDecibels(double decibels)
{
    static auto colors = std::array<sf::Color, 4>
    {
        NO_VOLUME,
        LOW_VOLUME,
        MID_VOLUME,
        HIGH_VOLUME
    };
    static auto decibelCenters = std::array<double, 4>
    {
        -40.0, -24.0, -9.0, -2.0
    };

    std::vector<double> distances;
    std::transform(decibelCenters.begin(), decibelCenters.end(),
                   std::back_inserter(distances),
                   [decibels](double x)
    {
       return std::abs(x - decibels);
    });

    auto minIterator = std::min_element(distances.begin(), distances.end());
    // TODO: Add interpolation
//    if(minIterator != distances.end())
//    {

//    }
//    else
//    {

//    }

    return colors[minIterator - distances.begin()];
}

static sf::Color interpolateColors(const sf::Color& left, const sf::Color& right, double t)
{
    // TODO: Implement linear interpolation between two colors
    return {};
}
}

#endif // COLORSCHEME_H
