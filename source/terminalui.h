#ifndef TERMINALUI_H
#define TERMINALUI_H

#include <memory>

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

    UiEvent queryInput() const;

private:
    TerminalUi();

    void drawTitle() const;
    void drawPitchIndicator();
    void drawInputSelector();
    void drawOptions();

private:
    double frequency{0.0};
    double volume{0.0};

    int rows{0};
    int columns{0};
};

#endif // TERMINALUI_H
