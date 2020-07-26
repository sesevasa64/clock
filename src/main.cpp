#include <iostream>
#include "../include/window.hpp"
#include "../lib/winbgim.hpp"
using namespace std;

int main() {
    //time_t cur = time(nullptr);
    //tm *tm_cur = localtime(&cur);
    //printf("%s", ctime(&cur));
    //printf("%d %d %d %d:%d:%d", tm_cur->tm_year + 1900, tm_cur->tm_mon,
    //    tm_cur->tm_mday, tm_cur->tm_hour, tm_cur->tm_min, tm_cur->tm_sec);

    const int width = 800, height = 600;
    window wd(width, height, "Clock");
    while(wd.is_open()) {
        wd.refresh();

        if(kbhit()) {
            wd.input(getch());
        }

        time_t cur = time(nullptr);
        outtextxy(width / 2, height / 2, ctime(&cur));

        wd.draw();
    }
    return 0;
}