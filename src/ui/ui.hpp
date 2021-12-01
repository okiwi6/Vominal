#pragma once
#include <curses.h>
#include <string>
#include <vector>

namespace ui {

class UIComponent {

};

class Highlight {
    public:
        static bool getHighlight(UIComponent&); 
        static bool releaseHighlight(UIComponent&);

    private:
        void createHighlight();
        Highlight();
        ui::Highlight me;
        bool anyoneHighlighted;
        UIComponent& highlighted;
}

}