#include "tunerui.h"

#include <string>

#include "colorscheme.h"
#include "uilayout.h"

// TODO: Remove this once sliding band class is finished
#include "musicutil.h"

TunerUi::TunerUi(unsigned int width, unsigned int height)
    : width(static_cast<float>(width)), height(static_cast<float>(height))
{
    font.loadFromFile("fonts/IBMPlexMono-Bold.ttf");
    text.setFont(font);
    text.setScale(0.8F, 0.8F);

    setupColors();
    arrangeLayout();
}

void TunerUi::drawOnto(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(slidingBand);
    window.draw(slidingBandWindow);
    window.draw(optionsMenuBookmark);
    window.draw(optionsMenu);

    text.setFillColor(COLORS::TEXT);

    // TODO: This is just for debugging, replace this
    // with the prepared graphical UI asap
    text.setPosition(220.0F, 180.0F);
    text.setString("Frequency");
    window.draw(text);

    text.setPosition(240.0F, 220.0F);
    text.setString(std::to_string(frequency));
    window.draw(text);

    text.setPosition(220.0F, 320.0F);
    text.setString("Closest Note");
    window.draw(text);

    text.setPosition(240.0F, 360.0F);
    auto note = MusicUtil::createNoteFromFrequency(frequency);
    text.setString(note.letter + std::to_string(note.octave));
    window.draw(text);

    text.setPosition(220.0F, 400.0F);
    text.setString("Deviation in Cents");
    window.draw(text);

    text.setPosition(240.0F, 440.0F);
    auto targetNoteFrequency = MusicUtil::getFrequencyOfNote(note);
    auto distanceInCents = MusicUtil::getDistanceBetweenFrequenciesInCents(frequency, targetNoteFrequency);
    text.setString(std::to_string(static_cast<int>(distanceInCents)));
    window.draw(text);

    text.setString("INPUT");
    text.setFillColor(COLORS::fromDecibels(volume));
    text.setPosition(width * LAYOUT::XOFFSET::VOLUME_INDICATOR,
                     height * LAYOUT::YOFFSET::VOLUME_INDICATOR);
    window.draw(text);
}

void TunerUi::displayFrequency(double frequency)
{
    // TODO: This will later tell the sliding band to display the given frequency
    this->frequency = frequency;
}

void TunerUi::displayVolume(double volume)
{
    this->volume = volume;
}

void TunerUi::arrangeLayout()
{
    background.setSize(sf::Vector2f(width, height));
    slidingBand.setSize(sf::Vector2f(width * LAYOUT::WIDTH::SLIDING_BAND,
                                     height * LAYOUT::HEIGHT::SLIDING_BAND));
    slidingBandWindow.setSize(sf::Vector2f(width * LAYOUT::WIDTH::SLIDING_BAND_WINDOW,
                                           height * LAYOUT::HEIGHT::SLIDING_BAND_WINDOW));
    optionsMenu.setSize(sf::Vector2f(width * LAYOUT::WIDTH::OPTIONS_MENU,
                                     height * LAYOUT::HEIGHT::OPTIONS_MENU));
    optionsMenuBookmark.setSize(sf::Vector2f(width * LAYOUT::WIDTH::OPTIONS_MENU_BOOKMARK,
                                             height * LAYOUT::HEIGHT::OPTIONS_MENU_BOOKMARK));

    slidingBand.setPosition(width * LAYOUT::XOFFSET::SLIDING_BAND, height * LAYOUT::YOFFSET::SLIDING_BAND);
    slidingBandWindow.setPosition(width * LAYOUT::XOFFSET::SLIDING_BAND_WINDOW,
                                  height * LAYOUT::YOFFSET::SLIDING_BAND_WINDOW);
    optionsMenu.setPosition(width * LAYOUT::XOFFSET::OPTIONS_MENU, height * LAYOUT::YOFFSET::OPTIONS_MENU);
    optionsMenuBookmark.setPosition(width * LAYOUT::XOFFSET::OPTIONS_MENU_BOOKMARK,
                                    height * LAYOUT::YOFFSET::OPTIONS_MENU_BOOKMARK);

    slidingBand.setOutlineThickness(LAYOUT::OUTLINE_THICKNESS::SLIDING_BAND);
    slidingBandWindow.setOutlineThickness(LAYOUT::OUTLINE_THICKNESS::SLIDING_BAND_WINDOW);
    optionsMenu.setOutlineThickness(LAYOUT::OUTLINE_THICKNESS::OPTIONS_MENU);
    optionsMenuBookmark.setOutlineThickness(LAYOUT::OUTLINE_THICKNESS::OPTIONS_MENU);
}

void TunerUi::setupColors()
{
    background.setFillColor(COLORS::BACKGROUND);

    slidingBand.setFillColor(COLORS::SLIDING_BAND);
    slidingBand.setOutlineColor(COLORS::OUTLINE);

    slidingBandWindow.setFillColor(COLORS::TRANSPARENT);
    slidingBandWindow.setOutlineColor(COLORS::OUTLINE);

    optionsMenu.setFillColor(COLORS::OPTIONS);
    optionsMenu.setOutlineColor(COLORS::OUTLINE);
    optionsMenuBookmark.setFillColor(COLORS::OPTIONS);
    optionsMenuBookmark.setOutlineColor(COLORS::OUTLINE);
}
