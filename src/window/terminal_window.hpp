#pragma once

#include <curses.h>

class TerminalWindow {
    public:
        TerminalWindow();
        ~TerminalWindow();
        TerminalWindow(const TerminalWindow&) = delete;
        TerminalWindow& operator=(const TerminalWindow&) = delete;

        void run();
    private:
        int terminal_width;
        int terminal_height;
};