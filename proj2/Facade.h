#ifndef FACADE_H_
#define FACADE_H_

#include <vector>
#include "Card.h"

class Facade {
    public:
        virtual ~Facade() {}
        virtual int getScore(int player) {}
        virtual int getDiscarded(int player) {}
        virtual std::vector<Card> getHand(int player) {}
        virtual bool** getTable() {}
        virtual int getCurrentPlayer() {}
        virtual bool getCurrentPlayerType() {}
    protected:
        Facade() {} //abstract base class
    private:
};

#endif

