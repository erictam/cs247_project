#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "PlayerHuman.h"
#include "PlayerComputer.h"
#include "Table.h"
#include "Command.h"

class Game {
public:
    Game ();
    void printDeck() {
        deck_.printDeck();
    }
    void printPlayerHand (int p);
    void takeTurn ();
    void determineFirstPlayer ();
private:
    Deck deck_;
    Player* players_[4];
    Table table_;
    int currentPlayer_;
};

#endif
