#pragma once

#include <curses.h>
#include <vector>
#include <string>
#include "../primitives/primitives.hpp"

namespace layout {
    
    class Layout {
        public:
            struct WindowNamePair{
                std::string name{};
                WINDOW* win{nullptr};
                primitives::BoundingBox bounds{};

                bool operator==(std::string other) {
                    return (name == other);
                }
            };

            Layout(WINDOW* win, std::string name="main");
            
            void splitLR(std::string windowName, int split, std::string name_left, std::string name_right);
            void splitUD(std::string windowNmae, int split, std::string name_up, std::string name_down);

            void drawBox(std::string);
            void drawBox(std::vector<WindowNamePair>::iterator);
            void drawBox(WINDOW*, int x0, int y0, int x1, int y1);

            std::vector<WindowNamePair>::iterator findWindow(std::string name);

        private:
            std::vector<WindowNamePair> windows;
    };
}