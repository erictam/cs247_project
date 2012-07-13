#ifndef FACADE_H_
#define FACADE_H_

#include <vector>
#include "Card.h"
#include "Subject.h"

// Enumerator to keep track of game states
enum GameState { NEWGAME, TAKETURN, NEXTROUND, FINISHEDGAME, QUITGAME };

class Facade : public Subject {
    public:
        virtual ~Facade() {}
        virtual int getScore(int player) const = 0;             // Gets the score of the player
        virtual int const* getScores() const = 0;               // Gets an array of the player scores
        virtual std::vector<Card> getDiscarded(int player) = 0; // Gets the list of discarded cards for a player
        virtual std::vector<Card> getHand(int player) = 0;      // Gets a list of cards a player has in their hand
        virtual bool const* getTable() const = 0;               // Returns an array of which cards have been played
        virtual int getCurrentPlayer() const = 0;               // Returns the current player number
        virtual bool getCurrentPlayerType() const = 0;          // Checks if a player is human or computer
        virtual int getCurrentTurn() const = 0;                 // Gets the game turn number
        virtual GameState getCurrentState() const = 0;          // Gets the current game state

        virtual int getDiscard(int) = 0;
        virtual int getWinner() const = 0;
    protected:
        Facade() {} //abstract base class
    private:
};

#endif

