#include "ui.hpp"

namespace ui {
    void Highlight::createHighlight() {
        me = Highlight();
    }

    static bool Highlight::getHighlight(UIComponent& comp) {
        if(!me) {
            createHighlight();
        }
    }
}