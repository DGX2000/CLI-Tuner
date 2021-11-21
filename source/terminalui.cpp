#include "terminalui.h"

#include <cmath>
#include <numeric>

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

void TerminalUi::updateInput(const std::string &input)
{
    this->input = input;
}

UiEvent TerminalUi::queryInput() const
{
    auto inputCharacter = terminal::getInput();
    if(inputCharacter == KEY_LEFT || inputCharacter == 'A' || inputCharacter == 'a')
    {
        return UiEvent::PREVIOUS_INPUT;
    }
    else if(inputCharacter == KEY_RIGHT || inputCharacter == 'D' || inputCharacter == 'd')
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
    static std::string title("CLI-Tuner");

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
    static std::string shortenedString;

    int center = columns / 2;
    int inputSelectorRow = 2 * rows / 3;

    auto stringPlacement = terminal::StringPlacement();

    int lengthAvailableForString =
            columns - static_cast<int>(leftEnd.length()) - static_cast<int>(rightEnd.length());
    shortenedString = input.substr(0, lengthAvailableForString);


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


    // TODO: Draw volume
    // 2 red blocks (0..-6dB)
    // 3 yellow blocks (-6dB..-15dB)
    // 4 green blocks (-15dB..-45dB)
    auto volumeInt = static_cast<int>(volume);
    const int maxGreenBlocks = 5;
    const int maxYellowBlocks = 3;
    const int maxRedBlocks = 2;

    const int greenThreshold = 30;
    const int yellowThreshold = 10;
    const int redThreshold = 4;

    int greenBlocks =
            std::min(1 + (volumeInt + greenThreshold)/((greenThreshold-yellowThreshold)/maxGreenBlocks),
                     maxGreenBlocks);
    int yellowBlocks =
            std::min(1 + (volumeInt + yellowThreshold)/((yellowThreshold-redThreshold)/maxYellowBlocks),
                     maxYellowBlocks);
    int redBlocks =
            std::min(1 + (volumeInt + redThreshold)/((redThreshold)/maxRedBlocks),
                     maxRedBlocks);

    auto charPlacement = terminal::CharPlacement();
    charPlacement.row = inputSelectorRow + 1;
    charPlacement.c = ' ';

    charPlacement.color = terminal::WHITE_TEXT_GREEN_BG;
    for(; greenBlocks > 0; --greenBlocks)
    {
        charPlacement.col = center - greenBlocks;
        terminal::put(charPlacement);

        charPlacement.col = center + greenBlocks;
        terminal::put(charPlacement);
    }

    charPlacement.color = terminal::WHITE_TEXT_YELLOW_BG;
    for(; yellowBlocks > 0; --yellowBlocks)
    {
        charPlacement.col = center - maxGreenBlocks - yellowBlocks;
        terminal::put(charPlacement);

        charPlacement.col = center + maxGreenBlocks + yellowBlocks;
        terminal::put(charPlacement);
    }

    charPlacement.color = terminal::WHITE_TEXT_RED_BG;
    for(; redBlocks > 0; --redBlocks)
    {
        charPlacement.col = center - maxGreenBlocks - maxYellowBlocks - redBlocks;
        terminal::put(charPlacement);

        charPlacement.col = center + maxGreenBlocks + maxYellowBlocks + redBlocks;
        terminal::put(charPlacement);
    }
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
