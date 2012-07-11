#ifndef FACADE_H_
#define FACADE_H_

#include <vector>
#include "Card.h"

class Facade {
    public:
        virtual ~Facade() {}
        virtual int getScore(int player) = 0;
        virtual int getDiscarded(int player) = 0;
        virtual std::vector<Card> getHand(int player) = 0;
        virtual bool* getTable() = 0;
        virtual int getCurrentPlayer() = 0;
        virtual bool getCurrentPlayerType() = 0;
    protected:
        Facade() {} //abstract base class
    private:
};

#endif

