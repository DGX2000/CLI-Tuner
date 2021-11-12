#ifndef TERMINALBRIDGE_H
#define TERMINALBRIDGE_H

namespace terminal
{
    #include <curses.h>

    constexpr short WHITE_TEXT_RED_BG = 1;
    constexpr short WHITE_TEXT_YELLOW_BG = 2;
    constexpr short WHITE_TEXT_GREEN_BG = 3;
    constexpr short WHITE_TEXT_CYAN_BG = 4;
    constexpr short WHITE_TEXT_BLACK_BG = 5;

    struct InitializationResult
    {
        bool hasColor{false};
    };

    InitializationResult initialize(int refreshRateFps)
    {
        initscr();

        keypad(stdscr, TRUE);
        timeout(1000 / refreshRateFps);
        curs_set(0);
        noecho();
        cbreak();
        raw();

        start_color();
        if(has_colors() == TRUE)
        {
            init_pair(WHITE_TEXT_RED_BG, COLOR_WHITE, COLOR_RED);
            init_pair(WHITE_TEXT_YELLOW_BG, COLOR_WHITE, COLOR_YELLOW);
            init_pair(WHITE_TEXT_GREEN_BG, COLOR_WHITE, COLOR_GREEN);
            init_pair(WHITE_TEXT_CYAN_BG, COLOR_WHITE, COLOR_CYAN);
            init_pair(WHITE_TEXT_BLACK_BG, COLOR_WHITE, COLOR_BLACK);

            return InitializationResult{true};
        }
        else
        {
            return InitializationResult{false};
        }
    }

    void finalize()
    {
        endwin();
    }

    int getInput()
    {
        return getch();
    }

    struct CharPlacement
    {
        int row;
        int col;
        char c;

        short color{WHITE_TEXT_BLACK_BG};
        bool bold{false};
    };

    void put(const CharPlacement& charPlacement)
    {
        if(charPlacement.bold)
        {
            attron(A_BOLD);
        }
        attron(COLOR_PAIR(charPlacement.color));

        mvaddch(charPlacement.row, charPlacement.col, charPlacement.c);

        if(charPlacement.bold)
        {
            attroff(A_BOLD);
        }
        attroff(COLOR_PAIR(charPlacement.color));
    }

    struct StringPlacement
    {
        int row;
        int col;
        const char* str;

        short color{WHITE_TEXT_BLACK_BG};
        bool bold{false};
    };

    void put(const StringPlacement& stringPlacement)
    {
        if(stringPlacement.bold)
        {
            attron(A_BOLD);
        }
        attron(COLOR_PAIR(stringPlacement.color));

        mvaddstr(stringPlacement.row, stringPlacement.col, stringPlacement.str);

        if(stringPlacement.bold)
        {
            attroff(A_BOLD);
        }
        attroff(COLOR_PAIR(stringPlacement.color));
    }

    struct Size
    {
        int rows;
        int columns;
    };

    Size getSize()
    {
        int rows{0}, columns{0};
        getmaxyx(stdscr, rows, columns);
        return Size{rows, columns};
    }
}



#endif // TERMINALBRIDGE_H
