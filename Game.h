#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "PlayerHuman.h"
#include "PlayerComputer.h"
#include "Table.h"
#include "Command.h"

class Game {
public:
    class QuitException {
    public:
        QuitException () {}
    };
    Game ();
    ~Game ();
    void printDeck() {
        deck_.printDeck();
    }
    void printPlayerHand (int p);
    void takeTurn ();
    void determineFirstPlayer ();
    void printTable ();
    void run ();
private:
    Deck deck_;
    Player* players_[4];
    int playerScores[4];
    Table table_;
    int currentPlayer_;
    int currentTurn_;
};

#endif
