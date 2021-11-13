#ifndef TERMINALUI_H
#define TERMINALUI_H

#include <string>

enum class UiEvent { PREVIOUS_INPUT, NEXT_INPUT, QUIT, NONE };

class TerminalUi
{
public:
    static constexpr int REFRESH_RATE_FPS = 25;

public:
    TerminalUi(TerminalUi&) = delete;
    void operator=(const TerminalUi&) = delete;

    ~TerminalUi();

    static TerminalUi& getInstance();

    void draw();

    void updateFrequency(double frequency);
    void updateVolume(double volume);
    void updateInput(const std::string& input);

    UiEvent queryInput() const;

private:
    TerminalUi();

    void drawTitle() const;
    void drawPitchIndicator() const;
    void drawInputSelector() const;
    void drawOptions() const;

private:
    std::string noteName;
    std::string input;
    int cents{0};

    double frequency{0.0};
    double volume{0.0};

    int rows{0};
    int columns{0};
};

#endif // TERMINALUI_H
