#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "../lib/winbgim.hpp"

struct Point {
    int x, y;
    Point() : Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}
};

typedef int Color;
double to_rad(double degree);

class Line {
protected:
    Point start, end;
    Color color;
    int thickness;
public:
    void draw();
    void setColor(Color color);
    void setThickness(int thickness);
    Line(Point start, Point end);
};

Line::Line(Point start, Point end) 
: start(start), end(end), color(WHITE), thickness(NORM_WIDTH) {}

void Line::draw() {
    int temp = getcolor();
    setcolor(color);
    line(start.x, start.y, end.x, end.y);
    setcolor(temp);
}

void Line::setColor(Color color) {
    this->color = color;
}
void Line::setThickness(int thickness) {
    this->thickness = thickness;
}

class Arrow : public Line {
private:
    int radius;
    int ratio;
public:
    Arrow(Point start, int radius, int ratio);
    void update(double value);
};

void Arrow::update(double value) {
    double arrow_angle = to_rad(value * ratio - 90);
    end.x = start.x + radius * cos(arrow_angle);
    end.y = start.y + radius * sin(arrow_angle);
}

Arrow::Arrow(Point start, int radius, int ratio) 
: radius(radius), ratio(ratio), Line(start, start) {}

double to_rad(double degree) {
    return degree * M_PI / 180.0;
}