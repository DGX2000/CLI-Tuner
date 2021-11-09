#include "tunerapplication.h"

#include <curses.h>
#include <locale.h>

// TODO:
// This is just a design mockup. Put all the curses stuff
// into its own namespace, and then write a Singleton Terminal
// class (constructor = curses init, destructor = curses exit)
// that the TunerApplication takes.
// Implement Main Loop: 1) Take input (with timeout 25ms), 2) Draw, 3) Refresh

void initializeCurses()
{
    // Initialize curses
    initscr();

    if(has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);

    // Delay for waiting for a character (25ms = 50Hz)
    timeout(25);

    // Read individual characters (not interested in reading whole lines)
    cbreak();

    // Don't buffer lines for input
    raw();

    // Don't output anything, when a key is pressed (e.g. no control characters)
    noecho();

    // Disable cursor
    curs_set(0);

    // Initialize input (F1..F12, Arrow Keys, etc.)
    keypad(stdscr, TRUE);
}

enum class INPUT_EVENTS { PREVIOUS_INPUT, NEXT_INPUT, QUIT, NONE };

INPUT_EVENTS handleInput()
{
    if(auto inputCharacter = getch(); inputCharacter == KEY_LEFT)
    {
        return INPUT_EVENTS::PREVIOUS_INPUT;
    }
    else if(inputCharacter == KEY_RIGHT)
    {
        return INPUT_EVENTS::NEXT_INPUT;
    }
    else if(inputCharacter == 'q' || inputCharacter == 'Q')
    {
        return INPUT_EVENTS::QUIT;
    }
    else
    {
        return INPUT_EVENTS::NONE;
    }
}

void drawTitle(int row, int columns)
{
    int column = 0.5F * columns - 7;
    attron(A_BOLD);
    mvaddstr(row, column, "CLI Tuner (0.1)");
    attroff(A_BOLD);
}

void drawPitch(int row, int columns)
{
    // If too small for slider => just draw text
    // If too small for text => bad luck
}

void drawInput(int row, int columns)
{

}

void drawOptions(int row, int columns)
{

}

void draw()
{
    clear();

    // Get window size
    int rows, columns;
    getmaxyx(stdscr, rows, columns);

    int title = 0;
    int pitch = 0.5F * rows;
    int input = 0.75F * rows;
    int options = rows;

    drawTitle(title, columns);
    drawPitch(pitch, columns);
    drawInput(input, columns);
    drawOptions(options, columns);

    // Draw everything
    refresh();
}

void finalizeCurses()
{
    endwin();
}

int main()
{
    initializeCurses();

    bool exitRequested{false};

    while(!exitRequested)
    {
        switch(handleInput())
        {
        case INPUT_EVENTS::PREVIOUS_INPUT:
            break;
        case INPUT_EVENTS::NEXT_INPUT:
            break;
        case INPUT_EVENTS::QUIT:
            exitRequested = true;
            break;
        case INPUT_EVENTS::NONE:
            break;
        }

        draw();
    }

    finalizeCurses();
}
