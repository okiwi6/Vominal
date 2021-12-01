#include "terminal_window.hpp"
#include <iostream>
#include <string>
#include "../primitives/primitives.hpp"
#include "../ui/layout.hpp"
#include "../ui/SelectableStringList.hpp"
#include "../audio/Recorder.hpp"
#include "../audio/OutputStream.hpp"

#include <chrono>
#include <thread>

TerminalWindow::TerminalWindow() {
    // inits the terminal screen
    initscr();
    // allows for detecting special keys
    keypad(stdscr, true);
    // turns off printing to terminal
    noecho();
    
    getmaxyx(stdscr, terminal_height, terminal_width);

    if(has_colors() == false) {
        throw std::runtime_error("The terminal doesn't support coloring");
    }

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void TerminalWindow::run() {
    //attron(COLOR_PAIR(1));

    layout::Layout super(stdscr, "main");
    super.drawBox("main");
    refresh();
    super.splitLR("main", 40, "left", "right");
    super.splitUD("right", terminal_height-10, "ru", "rd");
    clear();
    refresh();

    //attron(COLOR_PAIR(1));
    super.drawBox("left");
    super.drawBox("ru");
    super.drawBox("rd");
    refresh();
    SelectableStringList ssl(*super.findWindow("left"));

    ssl.addEntry("Hello");
    ssl.addEntry("World");
    ssl.addEntry("Moin");

    ssl.render();
    attron(COLOR_PAIR(2));

    move(10, 10);

    int c;
    while((c = getch()) != 'q') {
        switch(c) {
            case KEY_DOWN:
                primitives::drawText(stdscr, 1, 1, "KEYDOWN!");
                break;
            case 037 & KEY_DOWN:
                primitives::drawText(stdscr, 1, 1, "CTRL KEYDOWN!");
                break;

            default:
                primitives::drawText(stdscr, 1, 5, std::string(1, c));
                break;
        }
    }
}

TerminalWindow::~TerminalWindow() {
    endwin();
}