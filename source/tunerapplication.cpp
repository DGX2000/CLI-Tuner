#include "tunerapplication.h"

#include <algorithm>

#include "inpututil.h"

TunerApplication::TunerApplication()
    : ui(TerminalUi::getInstance()),
      tuningMediator(new TuningMediator())
{
    ui.updateInput(tuningMediator->getInput());
}

void TunerApplication::run()
{
    while(isRunning)
    {
        handleEvents();

        ui.updateFrequency(tuningMediator->getFundamentalFrequency());
        ui.updateVolume(tuningMediator->getVolume());

        display();
    }
}

void TunerApplication::handleEvents()
{
    auto event = ui.queryInput();
    switch(event)
    {
        case UiEvent::PREVIOUS_INPUT:
        switchToPreviousInput();
        break;

        case UiEvent::NEXT_INPUT:
        switchToNextInput();
        break;

        case UiEvent::QUIT:
        isRunning = false;
        break;

        case UiEvent::NONE:
        break;
    }
}

void TunerApplication::display()
{
    ui.draw();
}

void TunerApplication::switchToNextInput()
{
    auto inputs = InputUtil::getAllInputs();

    auto currentInput = std::find(inputs.begin(), inputs.end(), tuningMediator->getInput());
    if(currentInput != inputs.end() && currentInput != inputs.end()-1)
    {
        std::advance(currentInput, 1);

        tuningMediator->setInput(*currentInput);
        ui.updateInput(*currentInput);
    }
}

void TunerApplication::switchToPreviousInput()
{
    auto inputs = InputUtil::getAllInputs();

    auto currentInput = std::find(inputs.begin(), inputs.end(), tuningMediator->getInput());
    if(currentInput != inputs.begin() && currentInput != inputs.end())
    {
        std::advance(currentInput, -1);

        tuningMediator->setInput(*currentInput);
        ui.updateInput(*currentInput);
    }
}

