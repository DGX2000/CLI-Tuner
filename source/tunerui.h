#ifndef TUNERUI_H
#define TUNERUI_H

#include <SFML/Graphics.hpp>

class TunerUi
{
public:
    TunerUi(unsigned int width, unsigned int height);

    void drawOnto(sf::RenderWindow& window);

    void displayFrequency(double frequency);
    void displayVolume(double volume);

private:
    void arrangeLayout();
    void setupColors();

private:
    // TODO: Remove these once the UI is finished
    sf::Font font;
    sf::Text text;

    sf::RectangleShape background;

    // TODO: These are just for mocking up a design
    //       move these to classes later
    sf::RectangleShape slidingBand;
    sf::RectangleShape slidingBandWindow;
    sf::RectangleShape optionsMenu;
    sf::RectangleShape optionsMenuBookmark;
    sf::RectangleShape volumeIndicator;

    double frequency{0.0};
    double volume{0.0};
    float width, height;
};

#endif // TUNERUI_H
