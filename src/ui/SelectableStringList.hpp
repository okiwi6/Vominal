#pragma once

#include "../primitives/primitives.hpp"
#include "layout.hpp"

#include <vector>
#include <string>

class SelectableStringList {
    public:
        SelectableStringList(layout::Layout::WindowNamePair& frame);
        void render();
        void addEntry(std::string newEntry);
        void update();

    private:
        layout::Layout::WindowNamePair& wnp;
        std::vector<std::string> stringList;
        int currentPosition = 0;

        short primaryColor = 1;
        short highlightColor = 3;
};