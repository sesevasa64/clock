#pragma once
#include <vector>
#include <memory>
#include "builder.hpp"
#include "text.hpp"

typedef std::vector<std::shared_ptr<Line>> line_array;
typedef std::vector<std::shared_ptr<Arrow>> arrow_array;
typedef std::vector<std::shared_ptr<WindowText>> text_array;
typedef std::vector<std::string> string_array;

const int width  = 800; 
const int height = 600;
const int radius = 200;
const Point center(width / 2, height / 2);
const double small_offset = 0.04;
const double big_offset = 0.075;
const double time_offset = 0.09;

struct Setting {
    int color;
    int ratio;
    int radius;
};

const std::vector<Setting> settings = {{RED,  30, radius - 70}, // Часовая стрелка
                                       {GREEN, 6, radius - 30}, // Минутная стрелка
                                       {BLUE,  6, radius}};     // Секундная стрелка

arrow_array createArrows() {
    ArrowBuilder builder = ArrowBuilder().setStart(center);
    arrow_array result(settings.size());
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

line_array createLines() {
    LineBuilder builder;
    line_array lines(60);
    for(int i = 0, j = 0; i < 360; i += 6, j++) {
        Point start, end;
        auto angle = to_rad(i);
        if(i % 30 == 0) {
            start = Point((1 - big_offset) * radius * cos(angle), 
                          (1 - big_offset) * radius * sin(angle)) + center;
            end   = Point((1 + big_offset) * radius * cos(angle), 
                          (1 + big_offset) * radius * sin(angle)) + center;
        } 
        else {
            start = Point((1 - small_offset) * radius * cos(angle), 
                          (1 - small_offset) * radius * sin(angle)) + center;
            end   = Point((1 + small_offset) * radius * cos(angle), 
                          (1 + small_offset) * radius * sin(angle)) + center;
        }
        lines[j] = builder.setStart(start).setEnd(end).build();
    }
    return lines; 
}

text_array createText() {
    Point pos;
    text_array text(12);
    string_array hours = {"3", "4", "5", "6", "7", "8",     // Выглядит странно из-за
                          "9", "10", "11", "12", "1", "2"}; // поворота системы координат
    for(int i = 0, j = 0; i < 360; i += 30, j++) {
        auto angle = to_rad(i);
        pos = Point((1 + time_offset) * radius * cos(angle), 
                    (1 + time_offset) * radius * sin(angle)) + center;
        text[j] = std::make_shared<WindowText>(pos, hours[j]);
    }
    return text;
}