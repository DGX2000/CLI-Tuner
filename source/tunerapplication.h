#ifndef TUNERAPPLICATION_H
#define TUNERAPPLICATION_H

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "tunerui.h"
#include "tuningmediator.h"

class TunerApplication
{
public:
    static constexpr unsigned int WINDOW_WIDTH = 600;
    static constexpr unsigned int WINDOW_HEIGHT = 700;
    const std::string WINDOW_TITLE{"DG Tuner"};

public:
    TunerApplication();

    void run();

private:
    void handleEvents();
    void display();

private:
    sf::RenderWindow window;

    std::unique_ptr<TunerUi> ui;
    std::unique_ptr<TuningMediator> tuningMediator;
};

#endif // TUNERAPPLICATION_H
