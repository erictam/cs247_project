#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include "Command.h"

class Game {
public:
    class QuitException {           //quit exception class for QUIT command
    public:
        QuitException () {}
    };
    Game ();                        //public constructor
    ~Game ();                       //public destructor
    void printPlayerHand (int p);   //method to print player p's hand
    void takeTurn ();               //method to go through one player's turn
    void determineFirstPlayer ();   //method to determine the player holding the SEVEN SPADES card, who will go first
    void printTable ();             //method to print current cards on the table
    void run ();                    //method to start the game
private:
    Deck deck_;
    Player* players_[4];
    int playerScores_[4];
    Table table_;
    int currentPlayer_;
    int currentTurn_;
};

#endif
