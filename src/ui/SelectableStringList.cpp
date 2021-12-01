#include "SelectableStringList.hpp"

SelectableStringList::SelectableStringList(layout::Layout::WindowNamePair& frame):
    wnp(frame)
{

}

void SelectableStringList::addEntry(std::string other) {
    stringList.push_back(other);
}

void SelectableStringList::update() {

}

void SelectableStringList::render() {
    int xstart = wnp.bounds.x_ul + 1;
    int ystart = wnp.bounds.y_ul + 1;

    wattron(wnp.win, COLOR_PAIR(primaryColor));

    for(int i = 0; i < stringList.size(); i++) {
        primitives::drawText(wnp.win, xstart, ystart + i, stringList[i]);
    }
    //wrefresh(wnp.win);

    wattron(wnp.win, COLOR_PAIR(highlightColor));
    primitives::drawText(wnp.win, xstart, ystart + currentPosition, stringList[currentPosition], 40 - 1);
    wrefresh(wnp.win);
}
