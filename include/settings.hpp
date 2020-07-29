#pragma once
#include <vector>
#include <memory>
#include "builder.hpp"

const int width  = 800; 
const int height = 600;
const int radius = 200;
const Point center(width / 2, height / 2);

struct Setting {
    int color;
    int ratio;
    int radius;
};

const std::vector<Setting> settings = {{RED,  30, radius - 70}, // Часовая стрелка
                                       {GREEN, 6, radius - 30}, // Минутная стрелка
                                       {BLUE,  6, radius}};     // Секундная стрелка

std::vector<std::shared_ptr<Arrow>> createArrows() {
    ArrowBuilder builder = ArrowBuilder().setStart(center);
    std::vector<std::shared_ptr<Arrow>> result(settings.size());
    for(int i = 0; i < settings.size(); i++) {
        result[i] = builder
        .setRatio(settings[i].ratio)
        .setRadius(settings[i].radius)
        .setColor(settings[i].color)
        .setThickness(THICK_WIDTH)
        .build();
    }
    return result;
}

std::vector<std::shared_ptr<Line>> createLines() {
    LineBuilder builder;
    std::vector<std::shared_ptr<Line>> lines(60);
    for(int i = 0, j = 0; i < 360; i += 6, j++) {
        Point start, end;
        auto angle = to_rad(i);
        if(i % 30 == 0) {
            start = Point(0.925 * radius * cos(angle), 0.925 * radius * sin(angle)) + center;
            end   = Point(1.075 * radius * cos(angle), 1.075 * radius * sin(angle)) + center;
        } 
        else {
            start = Point(0.96 * radius * cos(angle), 0.96 * radius * sin(angle)) + center;
            end   = Point(1.04 * radius * cos(angle), 1.04 * radius * sin(angle)) + center;
        }
        lines[j] = builder.setStart(start).setEnd(end).build();
    }
    return lines; 
}