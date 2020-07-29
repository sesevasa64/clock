#include <iostream>
#include <vector>
#include <memory>
#include "../include/window.hpp"
#include "../include/arrow.hpp"
#include "../include/builder.hpp"
#include "../include/settings.hpp"
#include "../lib/winbgim.hpp"

using namespace std;

void drawClock(vector<shared_ptr<Line>>& lines, vector<shared_ptr<Arrow>>& arrows);

int main() {
    window wd(width, height, "Clock");

    auto arrows = createArrows();
    auto lines = createLines();

    while(wd.is_open()) {
        if(kbhit()) {
            wd.input(getch());
        }

        wd.refresh();

        time_t ctm = time(nullptr);
        tm *curr = localtime(&ctm);
        vector<double> time_array = {double(curr->tm_hour + curr->tm_min / 60.0), 
                                     double(curr->tm_min  + curr->tm_sec / 60.0), 
                                     double(curr->tm_sec)};
        for(int i = 0; i < arrows.size(); i++) {
            arrows[i]->update(time_array[i]);
        }

        drawClock(lines, arrows);
        wd.draw();
    }
    return 0;
}

void drawClock(vector<shared_ptr<Line>>& lines, vector<shared_ptr<Arrow>>& arrows) {
    circle(center.x, center.y, radius);
    for(auto line : lines) {
        line->draw();
    }
    for(auto& arrow : arrows) {
        arrow->draw();
    }
}

/*
auto arrows = vector<arrow*>();
for(auto& arroy : arrows) {
    arroy -> draw();
}
*/
//time_t cur = time(nullptr);
//tm *tm_cur = localtime(&cur);
//printf("%s", ctime(&cur));
//printf("%d %d %d %d:%d:%d", tm_cur->tm_year + 1900, tm_cur->tm_mon,
//    tm_cur->tm_mday, tm_cur->tm_hour, tm_cur->tm_min, tm_cur->tm_sec);
//outtextxy(width / 2, height / 2, ctime(&cur));

/*
auto hour_arrow = make_shared<movable_arrow>(center, radius, 15);
auto min_arrow = make_shared<movable_arrow>(center, radius, 6);
auto sec_arrow = make_shared<movable_arrow>(center, radius, 6);
*/