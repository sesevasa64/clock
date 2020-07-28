#pragma once
#include <memory>
#include "arrow.hpp"

class ArrowBuilder {
private:
    Point start;
    int radius;
    int ratio;
    Color color;
    int thickness;
public:
    ArrowBuilder() {}
    ArrowBuilder& setPoint(Point start) {
        this->start = start;
        return *this;
    }
    ArrowBuilder& setRadius(int radius) {
        this->radius = radius;
        return *this;
    }
    ArrowBuilder& setRatio(int ratio) {
        this->ratio = ratio;
        return *this;
    }
    ArrowBuilder& setColor(Color color) {
        this->color = color;
        return *this;
    }
    ArrowBuilder& setThickness(int thickness) {
        this->thickness = thickness;
        return *this;
    }
    std::shared_ptr<Arrow> build() {
        auto res = std::make_shared<Arrow>(start, radius, ratio);
        res->setThickness(thickness);
        res->setColor(color);
        return res;
    }
};

//auto ab = ArrowBuilder(Point(1,2), 4, 5).color(RED).thickness(4);
//auot arrow = ab.build();