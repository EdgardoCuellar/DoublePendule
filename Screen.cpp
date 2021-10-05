#include "Screen.hpp"

using namespace std;

Screen::Screen() noexcept = default;

Screen::~Screen() noexcept = default;

void Screen::init(const char *title, int xpos, int ypos, int wigth, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "All is init" << endl;

        window = SDL_CreateWindow(title, xpos, ypos, wigth, height, flags);
        if (window){
            cout << "Window created" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
            cout << "Renderer create" << endl;
        }

        isRunning = true;
    } else{
        isRunning = false;
    }
    centerP = Point(WITDH/2, HEIGHT/2 - 50, SIZEP/2, 2);
    createPendule();
}

void Screen::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    startPendule();
                    break;
            }

    }
}
void Screen::update(){
    if (isStart){
        float num1 = -G * (2 * SIZEP + SIZEP) * sin(pendules[0].getRadian());
        float num2 = -SIZEP * G * sin(pendules[0].getRadian()-2*pendules[1].getRadian());
        float num3 = -2*sin(pendules[0].getRadian()-pendules[1].getRadian())*SIZEP;
        float num4 = pendules[1].getSpeedDeg()*pendules[1].getSpeedDeg()*LENGHT+pendules[0].getSpeedDeg()*pendules[0].getSpeedDeg()*LENGHT*cos(pendules[0].getRadian()-pendules[1].getRadian());
        float den = LENGHT * (2*SIZEP+SIZEP-SIZEP*cos(2*pendules[0].getRadian()-2*pendules[1].getRadian()));

        pendules[0].setAcc((num1 + num2 + num3*num4) / den);

        num1 = 2 * sin(pendules[0].getRadian()-pendules[1].getRadian());
        num2 = (pendules[0].getSpeedDeg()*pendules[0].getSpeedDeg()*LENGHT*(SIZEP+SIZEP));
        num3 = G * (SIZEP + SIZEP) * cos(pendules[0].getRadian());
        num4 = pendules[1].getSpeedDeg()*pendules[1].getSpeedDeg()*LENGHT*SIZEP*cos(pendules[0].getRadian()-pendules[1].getRadian());
        den = LENGHT * (2*SIZEP+SIZEP-SIZEP*cos(2*pendules[0].getRadian()-2*pendules[1].getRadian()));
        pendules[1].setAcc((num1*(num2+num3+num4)) / den);

        pendules[0].setPosX(static_cast<int>(centerP.getPosX() + LENGHT*sin(pendules[0].getRadian())));
        pendules[0].setPosY(static_cast<int>(centerP.getPosY() + LENGHT*cos(pendules[0].getRadian())));

        pendules[1].setPosX(static_cast<int>(pendules[0].getPosX() + LENGHT*sin(pendules[1].getRadian())));
        pendules[1].setPosY(static_cast<int>(pendules[0].getPosY() + LENGHT*cos(pendules[1].getRadian())));

        for (int i = 0; i < 2; ++i) {
            pendules[i].addSpeed(pendules[i].getAcc());
            pendules[i].addDegre(pendules[i].getSpeedDeg());
            pendules[i].addSpeed(-pendules[i].getSpeedDeg()*RESISTANCE);
        }
        trace.push_back({static_cast<int>(pendules[1].getPosX()), static_cast<int>(pendules[1].getPosY())});
        if (TIMER != 0 && trace.size() > TIMER)
            trace.erase(trace.begin());
    }
}

void Screen::render(){
    // Background
    SDL_SetRenderDrawColor(renderer, COLORS[0][0], COLORS[0][1], COLORS[0][2], 255);
    SDL_RenderClear(renderer);
    if (isStart)
        displayTrace();
    // Display all point
    displayPendule();
    SDL_RenderPresent(renderer);
}

void Screen::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "All clean up" << endl;
}

void Screen::createPendule() noexcept {
    pendules[0] = Pendule(centerP.getPosX() + LENGHT * sin(pendules[0].getRadian()),
                          centerP.getPosY() + LENGHT * cos(pendules[0].getRadian()), SIZEP);
    pendules[1] = Pendule(pendules[0].getPosX() + LENGHT * sin(pendules[1].getRadian()),
                          pendules[0].getPosY() + LENGHT * cos(pendules[1].getRadian()), SIZEP);
}

void Screen::displayPendule() noexcept {
    displayLine();
    getPoints(centerP);
    getPoints(pendules[0]);
    getPoints(pendules[1]);
}

void Screen::displayLine() noexcept {
    SDL_SetRenderDrawColor(renderer, COLORS[3][0], COLORS[3][1], COLORS[3][2], 255);
    for (int i = -LINE_SIZE + 1; i < LINE_SIZE; ++i) {
        for (int j = -LINE_SIZE + 1; j < LINE_SIZE; ++j) {
            SDL_RenderDrawLine(renderer, static_cast<int>(centerP.getPosX())+i, static_cast<int>(centerP.getPosY())+j,
                               static_cast<int>(pendules[0].getPosX())+i, static_cast<int>(pendules[0].getPosY())+j);
        }
     }
    for (int i = -LINE_SIZE; i < LINE_SIZE; ++i) {
        for (int j = -LINE_SIZE+1; j < LINE_SIZE; ++j) {
            SDL_RenderDrawLine(renderer, static_cast<int>(pendules[0].getPosX())+i, static_cast<int>(pendules[0].getPosY())+j,
                               static_cast<int>(pendules[1].getPosX())+i, static_cast<int>(pendules[1].getPosY())+j);
        }
    }

}

void Screen::getPoints(Point &pt) noexcept {
    SDL_SetRenderDrawColor(renderer, COLORS[pt.getColor()][0], COLORS[pt.getColor()][1], COLORS[pt.getColor()][2], 255);
    vector<array<int, 2>> tmp = pt.getPoint();
    for (int i = 0; i < tmp.size()/2; ++i) {
        SDL_RenderDrawLine(renderer, tmp[i*2][0], tmp[i*2][1], tmp[(i*2)+1][0], tmp[(i*2)+1][1]);
    }
    SDL_RenderDrawLine(renderer, static_cast<int>(pt.getPosX())-pt.getPosR(), static_cast<int>(pt.getPosY()),
                       static_cast<int>(pt.getPosX())+pt.getPosR(), static_cast<int>(pt.getPosY()));
}

void Screen::displayTrace() noexcept {
    SDL_SetRenderDrawColor(renderer, COLORS[4][0], COLORS[4][1], COLORS[4][2], 255);
    for (int i = 0; i < trace.size()-1 ; ++i) {
        SDL_RenderDrawLine(renderer, trace[i][0], trace[i][1], trace[i+1][0], trace[i+1][1]);
    }

}

/*void Screen::createPoints(int nb) noexcept{
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> rdW(0, WITDH);
    uniform_real_distribution<double> rdH(0, HEIGHT);
    for (int i = 0; i < nb; ++i) {
        points.push_back(new Stars(rdW(mt), rdH(mt), sizeStars));
    }
}*/




