#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "../lib/winbgim.hpp"

double to_rad(double degree) {
    return degree * M_PI / 180.0;
}

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class arrow {
protected:
    Point start, end;
public:
    void draw();
    arrow(Point start, Point end);
};

arrow::arrow(Point start, Point end) 
: start(start), end(end) {}

void arrow::draw() {
    line(start.x, start.y, end.x, end.y);
}

class movable_arrow : public arrow {
private:
    int radius;
    int ratio;
public:
    movable_arrow(Point start, int radius, int ratio);
    void update(int value);
};

void movable_arrow::update(int value) {
    double arrow_angle = to_rad(value * ratio - 90);
    end.x = start.x + radius * cos(arrow_angle);
    end.y = start.y + radius * sin(arrow_angle);
}

movable_arrow::movable_arrow(Point start, int radius, int ratio) 
: radius(radius), ratio(ratio), arrow(start, start) {}