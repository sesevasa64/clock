#include <iostream>
#include <ctime>
#include "../lib/winbgim.hpp"
using namespace std;

int main() {
    time_t cur = time(nullptr);
    tm *tm_cur = localtime(&cur);
    printf("%s", ctime(&cur));
    printf("%d %d %d %d:%d:%d", tm_cur->tm_year + 1900, tm_cur->tm_mon,
        tm_cur->tm_mday, tm_cur->tm_hour, tm_cur->tm_min, tm_cur->tm_sec);
    return 0;
}