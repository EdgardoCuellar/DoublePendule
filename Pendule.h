#ifndef DOUBLEPENDULE_PENDULE_H
#define DOUBLEPENDULE_PENDULE_H

#include "Point.h"
#include <iostream>

int const LENGHT = 200;
int const SIZEP = 25;
float const RESISTANCE = 0.000;
float const G = 0.5;
const int LINE_SIZE = 2;
const int TIMER = 500;

class Pendule: public Point {

    float speedDeg = 0;
    float accDeg = 0;
    float degre = (170*3.14159f)/180;

public:
    // Constructeur
    Pendule() noexcept = default;
    Pendule(float x, float y, int radius) noexcept;

    // GETTER SETTER
    float getRadian() const noexcept {return degre;}
    float getSpeedDeg() const noexcept {return speedDeg;}
    float getAcc() const noexcept {return accDeg;}

    inline void setAcc(double a) noexcept {accDeg = static_cast<float>(a);}
    inline void addSpeed(float s) noexcept {speedDeg += s;}
    inline void addDegre(float d) noexcept {degre += d;}

    // Destructeur
    ~Pendule() noexcept override = default;

};

#endif //DOUBLEPENDULE_PENDULE_H
