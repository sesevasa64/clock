#pragma once
#include <vector>
#include <memory>
#include "builder.hpp"

const int width  = 800; 
const int height = 600;
const Point center(width / 2, height / 2);

struct Setting {
    int color;
    int ratio;
    int radius;
};

const std::vector<Setting> settings = {{RED,  30, 130}, 
                                       {GREEN, 6, 170}, 
                                       {BLUE,  6, 200}};

std::vector<std::shared_ptr<Arrow>> createArrows() {
    ArrowBuilder builder = ArrowBuilder().setPoint(center);
    std::vector<std::shared_ptr<Arrow>> result(settings.size());
    for(int i = 0; i < settings.size(); i++) {
        result[i] = builder
        .setRatio(settings[i].ratio)
        .setRadius(settings[i].radius)
        .setColor(settings[i].color)
        .build();
    }
    return result;
}