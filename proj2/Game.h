#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include "Command.h"
#include "Subject.h"
#include "Facade.h"
#include <string>

enum GameState { NEWGAME, TAKETURN, NEXTROUND, FINISHEDGAME };

class Game : public Subject, public Facade {
public:
    class QuitException {               //quit exception class for QUIT command
    public:
        QuitException () {}
    };
    Game ();                            //public constructor
    ~Game ();                           //public destructor
    void printPlayerHand (int p) const; //method to print player p's hand
    void takeTurn ();                   //method to go through one player's turn
    void determineFirstPlayer ();       //method to determine the player holding the SEVEN SPADES card, who will go first
    void printTable () const;           //method to print current cards on the table
    void run ();                        //method to start the game


    int getScore(int);
    int getDiscarded(int);
    std::vector<Card> getHand(int);
    bool const* getTable() const;
    int getCurrentPlayer();
    bool getCurrentPlayerType();

    void newGame();
    GameState getCurrentState();

    void setPlayers(std::string[]);

    void startGame();
    void tryPlayingCard(Card);
    void tryDiscardingCard(Card);

    void autoTurn();

private:
    Deck deck_;
    Player* players_[4];
    int playerScores_[4];
    Table table_;
    int currentPlayer_;
    int currentTurn_;
    GameState state_;
};

#endif
