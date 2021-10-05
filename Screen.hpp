#ifndef SDL2_TEST_SCREEN_HPP
#define SDL2_TEST_SCREEN_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <array>
#include "Point.h"
#include "Pendule.h"
#include <random>
#include <vector>

// OPTION
int const WITDH = 1000;
int const HEIGHT = 1000;
int const COLORS[5][3] = {{30,30,30}, {180,180,180}, {100, 100, 100}, {250, 250, 250}, {98, 0, 234}};

class Screen{
    bool isRunning{};
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    bool isStart = false;
    Point centerP;
    std::array<Pendule, 2> pendules;
    std::vector<std::array<int, 2>> trace;

public:
    Screen () noexcept;
    ~Screen() noexcept;

    void init(const char* title, int xpos, int ypos, int wigth, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    void createPendule() noexcept;
    void displayPendule() noexcept;
    void displayLine() noexcept;
    void displayTrace() noexcept;
    inline void getPoints(Point& pt) noexcept;
    inline void startPendule() noexcept {isStart = true;}

    bool running() const {return isRunning; };
};

#endif //SDL2_TEST_SCREEN_HPP
