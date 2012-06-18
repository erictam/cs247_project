#include <iostream>
#include <stdlib.h>
#include "Game.h"

int main(int argc, char* argv[]) {
    int randSeed;

    //seed the random number generator
    if (argc > 1) {
        randSeed = atoi(argv[1]);
        srand48 (randSeed);
    }
    
    //create a new game and run it
    Game* game = new Game();
    game->run();
    
    delete game;
    
    return 0;
    
}
