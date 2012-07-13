#ifndef _GAME_
#define _GAME_

#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include "Command.h"
#include "Subject.h"
#include "Facade.h"
#include <string>



class Game : public Facade {
public:
    class QuitException {               //quit exception class for QUIT command
    public:
        QuitException () {}
    };
    Game ();                            //public constructor
    ~Game ();                           //public destructor
    void takeTurn ();                   //method to go through one player's turn
    void determineFirstPlayer ();       //method to determine the player holding the SEVEN SPADES card, who will go first

    int getScore(int) const;
    int const* getScores() const;
    int getDiscard(int);
    std::vector<Card> getDiscarded(int);
    std::vector<Card> getHand(int);
    bool const* getTable() const;
    int getCurrentPlayer() const;
    bool getCurrentPlayerType() const;
    int getCurrentTurn() const;
    GameState getCurrentState() const;
    int getWinner() const;

    void setPlayers(std::string[], int);

    void startGame();
    void endGame();
    void tryPlayingCard(int);
    void tryDiscardingCard(int);

    void autoTurn();
    void checkForRoundComplete();

    void rageQuit(int);


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
