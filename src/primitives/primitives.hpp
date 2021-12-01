#pragma once
#include <curses.h>
#include <math.h>
#include <string>

namespace primitives {
    class BoundingBox {
        public:
            BoundingBox() {

            }
            BoundingBox(int x0, int y0, int x1, int y1) {
                x_ul = std::min(x0, x1);
                y_ul = std::min(y0, y1);
                x_dr = std::max(x0, x1);
                y_dr = std::max(y0, y1);
            }

            BoundingBox cutx_left(int xcut);
            BoundingBox cutx_right(int xcut);
            BoundingBox cuty_up(int ycut);
            BoundingBox cuty_down(int ycut);

            WINDOW* winFromBounds();

            int x_ul, y_ul;
            int x_dr, y_dr;
    };

    void drawText(WINDOW* win, int x, int y, std::string text, int len=-1);
}