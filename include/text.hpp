#pragma once
#include <string>
#include "arrow.hpp"

class WindowText {
private:
    std::string text;
    Point pos;
public:
    WindowText(Point pos, std::string text)
    : pos(pos), text(text) {}
    void draw() {
        int x_offset = textwidth(text.c_str()) / 2;
        int y_offset = textheight(text.c_str()) / 2;
        outtextxy(pos.x - x_offset, pos.y - y_offset, text.c_str());
    }
};