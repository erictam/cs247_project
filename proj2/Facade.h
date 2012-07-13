#ifndef FACADE_H_
#define FACADE_H_

#include <vector>
#include "Card.h"
#include "Subject.h"

enum GameState { NEWGAME, TAKETURN, NEXTROUND, FINISHEDGAME, QUITGAME };

class Facade : public Subject {
    public:
        virtual ~Facade() {}
        virtual int getScore(int player) const = 0;
        virtual int const* getScores() const = 0;
        virtual std::vector<Card> getDiscarded(int player) = 0;
        virtual std::vector<Card> getHand(int player) = 0;
        virtual bool const* getTable() const = 0;
        virtual int getCurrentPlayer() const = 0;
        virtual bool getCurrentPlayerType() const = 0;
        virtual int getCurrentTurn() const = 0;
        virtual GameState getCurrentState() const = 0;

        virtual int getDiscard(int) = 0;
        virtual int getWinner() const = 0;
    protected:
        Facade() {} //abstract base class
    private:
};

#endif

