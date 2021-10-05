#include <iostream>
#include "Screen.hpp"

int main(int argc, char* argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 /FPS;

    Uint32 frameStart;
    int frameTime;

    Screen *screen = new Screen();
    screen->init("Double Pendule", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WITDH, HEIGHT, false);

    while (screen->running()){
        frameStart = SDL_GetTicks();

        screen->handleEvents();
        screen->update();
        screen->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    screen->clean();

    return 0;
}
