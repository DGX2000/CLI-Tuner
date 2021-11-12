#include "tunerapplication.h"

TunerApplication::TunerApplication()
    : ui(TerminalUi::getInstance()),
      tuningMediator(new TuningMediator())
{

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
        // TODO: Tuning mediator, previous input
        break;

        case UiEvent::NEXT_INPUT:
        // TODO: Tuning mediator, next input
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

