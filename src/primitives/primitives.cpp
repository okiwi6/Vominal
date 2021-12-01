#include "primitives.hpp"

namespace primitives {
    BoundingBox BoundingBox::cutx_left(int xcut) {
        return BoundingBox(x_ul, y_ul, xcut + 1, y_dr);
    }
    BoundingBox BoundingBox::cutx_right(int xcut) {
        return BoundingBox(xcut+1, y_ul, x_dr, y_dr);
    }
    BoundingBox BoundingBox::cuty_up(int ycut) {
        return BoundingBox(x_ul, y_ul, x_dr, ycut + 1);
    }
    BoundingBox BoundingBox::cuty_down(int ycut) {
        return BoundingBox(x_ul, ycut+1, x_dr, y_dr);
    }

    WINDOW* BoundingBox::winFromBounds() {
        return newwin(y_dr - y_ul, x_dr - x_ul, y_ul, x_ul);
    }

    void drawText(WINDOW* win, int x, int y, std::string text, int len) {
        // print text at xy
        mvwprintw(win, y, x, text.c_str());
        if(len != -1) {
            // also fill rest with whitespaces so that color is correct
            std::string rest(len - text.size(), ' ');
            wprintw(win, rest.c_str());
        }
    }
}