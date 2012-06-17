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

    Game game;

    /*game.printDeck();


    game.printPlayerHand(1);
    game.printPlayerHand(2);
    game.printPlayerHand(3);
    game.printPlayerHand(4);*/
    
    game.determineFirstPlayer();

    while (true) { 
        game.takeTurn();
    }
    
}
