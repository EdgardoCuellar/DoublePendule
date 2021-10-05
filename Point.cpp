#include "Point.h"

using namespace std;

Point::Point() noexcept : posX(0), posY(0), radius(0), color(0) {}

Point::Point(float x, float y, int r, int c) noexcept : posX(x), posY(y), radius(r), color(c) {}

vector<array<int, 2>> Point::getPoint() const noexcept {
    vector<array<int, 2>> points;
    int x = radius, y = 0;
    int p = 1 - radius;

    while (x > y){
        y++;

        if (p <= 0)
            p = p + 2*y + 1;
        else{
            x--;
            p = p + 2*y - 2*x + 1;
        }
        if (x < y)
            break;

        points.push_back({(x + static_cast<int>(posX)), (y + static_cast<int>(posY))});
        points.push_back({(-x + static_cast<int>(posX)), (y + static_cast<int>(posY))});
        points.push_back({(x + static_cast<int>(posX)), (-y + static_cast<int>(posY))});
        points.push_back({(-x + static_cast<int>(posX)), (-y + static_cast<int>(posY))});

        if (x != y){
            points.push_back({(y + static_cast<int>(posX)), (x + static_cast<int>(posY))});
            points.push_back({(-y + static_cast<int>(posX)), (x + static_cast<int>(posY))});
            points.push_back({(y + static_cast<int>(posX)), (-x + static_cast<int>(posY))});
            points.push_back({(-y + static_cast<int>(posX)), (-x + static_cast<int>(posY))});
        }
    }
    return points;
}
