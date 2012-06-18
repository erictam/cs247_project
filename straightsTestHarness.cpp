#include <iostream>
#include <stdlib.h>
#include "Game.h"

int main(int argc, char* argv[]) {
    Command command;
    std::string input;
    int randSeed;

    if (argc > 1) {
        randSeed = atoi(argv[1]);
        srand48 (randSeed);
    }

    //Game game;
    //game.run();
    Game* game = new Game();
    game->run();
    
    delete game;
    
    return 0;
    
}
