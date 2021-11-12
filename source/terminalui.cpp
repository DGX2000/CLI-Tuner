#include "terminalui.h"

#include <string>

#include "terminalbridge.h"

TerminalUi::TerminalUi()
{
    terminal::initialize(REFRESH_RATE_FPS);
}

TerminalUi::~TerminalUi()
{
    terminal::finalize();
}

TerminalUi& TerminalUi::getInstance()
{
    static TerminalUi instance;
    return instance;
}

void TerminalUi::draw()
{
    terminal::clear();

    auto size = terminal::getSize();
    this->rows = size.rows;
    this->columns = size.columns;

    drawTitle();
    drawPitchIndicator();
    drawInputSelector();
    drawOptions();

    terminal::refresh();
}

void TerminalUi::updateFrequency(double frequency)
{
    this->frequency = frequency;
    // TODO: Create note, create display string from that note
    // also get cents (remove frequency)
}

void TerminalUi::updateVolume(double volume)
{
    this->volume = volume;
}

UiEvent TerminalUi::queryInput() const
{
    auto inputCharacter = terminal::getInput();
    if(inputCharacter == KEY_LEFT)
    {
        return UiEvent::PREVIOUS_INPUT;
    }
    else if(inputCharacter == KEY_RIGHT)
    {
        return UiEvent::NEXT_INPUT;
    }
    else if(inputCharacter == 'q' || inputCharacter == 'Q')
    {
        return UiEvent::QUIT;
    }
    else
    {
        return UiEvent::NONE;
    }
}

void TerminalUi::drawTitle() const
{
    static std::string title("CLI Tuner (0.1)");

    int center = columns / 2;
    int titleStart = center - static_cast<int>(title.length()) / 2;

    auto stringPlacement = terminal::StringPlacement();
    stringPlacement.row = 0;
    stringPlacement.col = titleStart;
    stringPlacement.str = title.c_str();
    stringPlacement.bold = true;

    terminal::put(stringPlacement);
}

void TerminalUi::drawPitchIndicator()
{
    static std::string leftEnd("-50");
    static std::string rightEnd("+50");
    static std::string note("C#0"); // TODO: This is of course dynamic later

    int scaleRow = rows / 3;

    int center = columns / 2;
    int scaleWidth = columns - 6; // '-50' and '+50' on the sides are fixed

    auto stringPlacement = terminal::StringPlacement();

    stringPlacement.row = scaleRow;
    stringPlacement.col = 0;
    stringPlacement.str = leftEnd.c_str();
    terminal::put(stringPlacement);

    stringPlacement.col += scaleWidth + static_cast<int>(leftEnd.length());
    stringPlacement.str = rightEnd.c_str();
    terminal::put(stringPlacement);

    stringPlacement.str = note.c_str();
    stringPlacement.bold = true;



    int scaleStart = static_cast<int>(leftEnd.length());
    int markers = 11; // Make static constexpr
    int divisionWidth = scaleWidth / (markers - 1);

    auto charPlacement = terminal::CharPlacement();
    charPlacement.row = scaleRow;
    charPlacement.c = '|';
    for(int i = 0; i < markers; ++i)
    {
        if(i != markers / 2)
        {
            charPlacement.col = scaleStart + i * divisionWidth;
            terminal::put(charPlacement);
        }
        else
        {
            stringPlacement.col = center - 1;
            terminal::put(stringPlacement);
        }
    }


    int indicatorRow = scaleRow + 1;
}

void TerminalUi::drawInputSelector()
{
//    int cols_left = 0.25F * columns;
//    int cols_middle = 0.5F * columns - 5;
//    int cols_right = 0.75F * columns;

//    mvaddch(row, cols_left, '<');
//    mvaddch(row, cols_right, '>');

//    mvaddstr(row, cols_middle, "INPUT #0");
}

void TerminalUi::drawOptions()
{
//    move(row, 0);

//    addstr("QQuit ");
//    addstr("LeftPrevious Input ");
//    addstr("RightPrevious Input ");
}
