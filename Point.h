#ifndef SDL2_TEST_POINT_H
#define SDL2_TEST_POINT_H

#include <vector>
#include <array>
#include <cmath>

class Point {
    float posX;
    float posY;
    int radius;
    int color;

protected:
    inline void movePosX(float x) noexcept {posX += x;}
    inline void movePosY(float y) noexcept {posY += y;}

public:
    // Constructeur
    Point() noexcept;
    Point(float x, float y, int radius, int c) noexcept;
    // Destructeur
    virtual ~Point() noexcept = default;
    // GETTER SETTER
    float getPosX() const noexcept {return posX;}
    float getPosY() const noexcept {return posY;}
    inline void setPosX(int x) noexcept {posX = static_cast<float>(x);}
    inline void setPosY(int y) noexcept {posY = static_cast<float>(y);}
    int getPosR() const noexcept {return radius;}
    int getColor() const noexcept {return color;}

    // Dynamics things
    std::vector<std::array<int, 2>> getPoint() const noexcept;
};


#endif //SDL2_TEST_POINT_H
