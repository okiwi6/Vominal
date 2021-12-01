#include "layout.hpp"
#include <algorithm>

namespace layout {
    Layout::Layout(WINDOW* win, std::string name) {
        WindowNamePair entry;
        entry.win = win;
        entry.name = name;
        
        int xdim, ydim;
        getmaxyx(win, ydim, xdim);
        entry.bounds = primitives::BoundingBox{0, 0, xdim, ydim};

        windows.push_back(std::move(entry));
    }

    void Layout::splitLR(std::string name, int xsplit, std::string name_left, std::string name_right) {
        std::vector<Layout::WindowNamePair>::iterator wnp = findWindow(name);
        
        WindowNamePair left;
        left.name = name_left;
        left.bounds = wnp -> bounds.cutx_left(xsplit);
        left.win = left.bounds.winFromBounds();

        WindowNamePair right;
        right.name = name_right;
        right.bounds = wnp -> bounds.cutx_right(xsplit);
        right.win = right.bounds.winFromBounds();

        wclear(wnp -> win);
        windows.erase(wnp);

        windows.push_back(left);
        windows.push_back(right);
        refresh();
    }

    void Layout::splitUD(std::string name, int ysplit, std::string name_up, std::string name_down) {
        std::vector<Layout::WindowNamePair>::iterator wnp = findWindow(name);

        WindowNamePair up;
        up.name = name_up;
        up.bounds = wnp -> bounds.cuty_up(ysplit);
        up.win = up.bounds.winFromBounds();

        WindowNamePair down;
        down.name = name_down;
        down.bounds = wnp -> bounds.cuty_down(ysplit);
        down.win = down.bounds.winFromBounds();

        wclear(wnp -> win);
        windows.erase(wnp);

        windows.push_back(up);
        windows.push_back(down);
        refresh();
    }

    std::vector<Layout::WindowNamePair>::iterator Layout::findWindow(std::string name) {
        // returns the main window if the query cannot be fulfilled
        std::vector<WindowNamePair>::iterator item = std::find(windows.begin(), windows.end(), name);

        if(item != windows.end()) {
            return item;
        }

        // for(auto wnp : windows) {
        //     if(wnp.name == name) {
        //         return wnp;
        //     }
        // }
        return windows.begin();
    }

    void Layout::drawBox(std::string name) {
        drawBox(findWindow(name));
    }

    void Layout::drawBox(std::vector<WindowNamePair>::iterator window) {
        box(window -> win, 0, 0);
        // int xmax, ymax;
        // getmaxyx(window -> win, ymax, xmax);

        // drawBox(window -> win, 0, 0, xmax, ymax);
        wrefresh(window -> win);
    }

    void Layout::drawBox(WINDOW* window, int x0, int y0, int x1, int y1) {
        primitives::BoundingBox bounds{x0, y0, x1, y1};

        mvwhline(window, bounds.y_ul, bounds.x_ul, 0, bounds.x_dr-bounds.x_ul);
        mvwhline(window, bounds.y_dr, bounds.x_ul, 0, bounds.x_dr-bounds.x_ul);
        mvwvline(window, bounds.y_ul, bounds.x_ul, 0, bounds.y_dr-bounds.y_ul);
        mvwvline(window, bounds.y_ul, bounds.x_dr, 0, bounds.y_dr-bounds.y_ul);

        // add corners
        mvaddch(bounds.y_ul, bounds.x_ul, ACS_ULCORNER);
        mvaddch(bounds.y_ul, bounds.x_dr, ACS_URCORNER);
        mvaddch(bounds.y_dr, bounds.x_ul, ACS_LLCORNER);
        mvaddch(bounds.y_dr, bounds.x_dr, ACS_LRCORNER);
    }

}