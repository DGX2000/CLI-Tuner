#ifndef TUNERAPPLICATION_H
#define TUNERAPPLICATION_H

#include <memory>
#include <string>

#include "terminalui.h"
#include "tuningmediator.h"

class TunerApplication
{
public:
    TunerApplication();
    void run();

private:
    void handleEvents();
    void display();

    void switchToNextInput();
    void switchToPreviousInput();

private:
    TerminalUi& ui;
    std::unique_ptr<TuningMediator> tuningMediator;
    bool isRunning{true};
};

#endif // TUNERAPPLICATION_H
