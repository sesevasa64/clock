#pragma once
#include <memory>
#include "arrow.hpp"

class LineBuilder {
protected:
    Point start;
    Point end;
    Color color;
    int thickness;
public:
    LineBuilder& setStart(Point start) {
        this->start = start;
        return *this;
    }
    LineBuilder& setEnd(Point end) {
        this->end = end;
        return *this;
    }
    LineBuilder& setColor(Color color) {
        this->color = color;
        return *this;
    }
    LineBuilder& setThickness(int thickness) {
        this->thickness = thickness;
        return *this;
    }
    std::shared_ptr<Line> build() {
        auto res = std::make_shared<Line>(start, end);
        setOptional(res);
        return res;
    }
    LineBuilder() : color(WHITE), thickness(NORM_WIDTH) {}
protected:
    void setOptional(std::shared_ptr<Line> ptr) {
        ptr->setThickness(thickness);
        ptr->setColor(color);
    }
};

class ArrowBuilder : public LineBuilder {
private:
    int radius;
    int ratio;
public:
    ArrowBuilder& setRadius(int radius) {
        this->radius = radius;
        return *this;
    }
    ArrowBuilder& setRatio(int ratio) {
        this->ratio = ratio;
        return *this;
    }
    ArrowBuilder& setStart(Point start) {
        LineBuilder::setStart(start);
        return *this;
    }
    ArrowBuilder& setEnd(Point end) {
        LineBuilder::setEnd(end);
        return *this;
    }
    ArrowBuilder& setColor(Color color) {
        LineBuilder::setColor(color);
        return *this;
    }
    ArrowBuilder& setThickness(int thickness) {
        LineBuilder::setThickness(thickness);
        return *this;
    }
    std::shared_ptr<Arrow> build() {
        auto res = std::make_shared<Arrow>(start, radius, ratio);
        setOptional(res);
        return res;
    }
    ArrowBuilder() : LineBuilder() {}
};

//auto ab = ArrowBuilder(Point(1,2), 4, 5).color(RED).thickness(4);
//auot arrow = ab.build();