#include <iostream>
#include "src/Game.h"
#include "util/log.h"
#include "src/Constants.h"


int main(int argc, char *argv[])
{
    const int FPS = Constant::FPS;
    const int frameDelay = 1000 / FPS;
    
    Game game;
    game.init("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080);
    
    Uint32 frameStart, frameTime;
    while (game.running()) {
        frameStart = SDL_GetTicks();

        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    game.clean();
    
    return EXIT_SUCCESS;
}