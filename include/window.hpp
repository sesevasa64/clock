#pragma once
#include <ctime>
#include <string>
#include "../lib/winbgim.hpp"

/*
window wd(800, 600, "title")
while(wd.is_open()) {
    // get user input
    // update game logic
    // draw on screen
}
*/

class window {
private:
    int width;
    int height;
    std::string title;
    int frame_id;
    bool open;
public:
    void input(int key);
    void refresh();
    void draw();
    bool is_open();
    window(int width, int height, std::string title);
    ~window();
};

void window::input(int key) {
    if(key == KEY_ESC) {
        open = false;
    }
}

void window::refresh() {
    setactivepage(frame_id);
    setbkcolor(BLACK);
    clearviewport();
}

void window::draw() {
    setvisualpage(frame_id);
    frame_id = 1 - frame_id;
} 

bool window::is_open() {
    return open;
}

window::window(int width, int height, std::string title) 
: width(width), height(height), title(title), open(true), frame_id(1) {
    initwindow(this->width, this->height, title.c_str());
}

window::~window() {
    closegraph();
}