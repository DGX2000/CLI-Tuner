#include "terminalui.h"

#include <cmath>

#include "musicutil.h"
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

    auto note = MusicUtil::createNoteFromFrequency(frequency);

    noteName = note.letter;
    if(noteName.length() == 1)
    {
        noteName.push_back(' ');
    }
    noteName += std::to_string(note.octave);

    auto targetFrequency = MusicUtil::getFrequencyOfNote(note);
    this->cents = MusicUtil::getDistanceBetweenFrequenciesInCents(frequency, targetFrequency);
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

void TerminalUi::drawPitchIndicator() const
{
    static std::string leftEnd("-50");
    static std::string rightEnd("+50");

    int scaleRow = rows / 3;
    int center = columns / 2;

    auto stringPlacement = terminal::StringPlacement();

    stringPlacement.row = scaleRow;
    stringPlacement.col = 0;
    stringPlacement.str = leftEnd.c_str();
    terminal::put(stringPlacement);

    stringPlacement.col += columns -  static_cast<int>(leftEnd.length());
    stringPlacement.str = rightEnd.c_str();
    terminal::put(stringPlacement);

    stringPlacement.col = center - 1;
    stringPlacement.str = noteName.c_str();
    stringPlacement.bold = true;
    // TODO: Make 6 constexpr for acceptable tuning threshold
    if(std::abs(cents) < 6)
    {
        stringPlacement.color = terminal::WHITE_TEXT_GREEN_BG;
    }
    else if(std::abs(cents) < 12)
    {
        stringPlacement.color = terminal::WHITE_TEXT_YELLOW_BG;
    }
    terminal::put(stringPlacement);



    int scaleStart = center;
    int markersOnAHalf = 5; // Make static constexpr
    int divisionWidth = (columns/2 - 3) / markersOnAHalf;

    auto charPlacement = terminal::CharPlacement();
    charPlacement.row = scaleRow;
    charPlacement.c = '|';
    for(int i = 1; i <= markersOnAHalf; ++i)
    {
        charPlacement.col = scaleStart - i * divisionWidth;
        terminal::put(charPlacement);

        charPlacement.col = scaleStart + i * divisionWidth;
        terminal::put(charPlacement);
    }


    int indicatorRow = scaleRow + 1;
    charPlacement.row = indicatorRow;
    charPlacement.col = scaleStart + (cents * divisionWidth) / 10;
    charPlacement.c = '^';
    charPlacement.bold = true;
    terminal::put(charPlacement);
    // -50 would be scaleStart - 5 * divisionWidth
    // +50 would be scaleStart + 5 * divisionWidth
    // => so do scaleStart + (cents/10.0) * divisionWidth
}

void TerminalUi::drawInputSelector() const
{
    static std::string leftEnd(" < ");
    static std::string rightEnd(" > ");
    static std::string sampleInput("SAMPLE INPUT MIGHT BE VERY LONG SO THIS NEEDS SOME SOLUTIONNNN");
    static std::string shortenedString;

    int center = columns / 2;
    int inputSelectorRow = 2 * rows / 3;

    auto stringPlacement = terminal::StringPlacement();

    int lengthAvailableForString =
            columns - static_cast<int>(leftEnd.length()) - static_cast<int>(rightEnd.length());
    shortenedString = sampleInput.substr(0, lengthAvailableForString);


    stringPlacement.row = inputSelectorRow;
    stringPlacement.col = center - static_cast<int>(shortenedString.length()) / 2;
    stringPlacement.str = shortenedString.c_str();
    terminal::put(stringPlacement);

    stringPlacement.col =
            center - static_cast<int>(shortenedString.length()) / 2 - static_cast<int>(leftEnd.length());
    stringPlacement.str = leftEnd.c_str();
    terminal::put(stringPlacement);

    stringPlacement.col =
            center + static_cast<int>(shortenedString.length()) / 2;
    stringPlacement.str = rightEnd.c_str();
    terminal::put(stringPlacement);
}

void TerminalUi::drawOptions() const
{
    int spacing = 3; // make constexpr in class

    static std::string quit("Quit");
    static std::string prevInput("Previous Input");
    static std::string nextInput("Next Input");

    auto charPlacement = terminal::CharPlacement();
    auto stringPlacement = terminal::StringPlacement();

    charPlacement.row = rows-1;
    charPlacement.bold = true;
    stringPlacement.row = rows - 1;
    stringPlacement.color = terminal::WHITE_TEXT_CYAN_BG;

    charPlacement.c = 'Q';
    terminal::put(charPlacement);

    stringPlacement.col = charPlacement.col + 1;
    stringPlacement.str = quit.c_str();
    terminal::put(stringPlacement);

    charPlacement.col += static_cast<int>(quit.length()) + spacing;
    charPlacement.c = 'A';
    terminal::put(charPlacement);

    stringPlacement.col = charPlacement.col + 1;
    stringPlacement.str = prevInput.c_str();
    terminal::put(stringPlacement);

    charPlacement.col += static_cast<int>(prevInput.length()) + spacing;
    charPlacement.c = 'D';
    terminal::put(charPlacement);

    stringPlacement.col = charPlacement.col + 1;
    stringPlacement.str = nextInput.c_str();
    terminal::put(stringPlacement);
}
