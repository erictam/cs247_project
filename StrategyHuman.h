#ifndef _STRATEGYHUMAN_
#define _STRATEGYHUMAN_

#include "Strategy.h"

class StrategyHuman : public Strategy {
public:
    class IllegalMoveException {                                //illegal move exception, only applies to strategyHuman
    public:
        IllegalMoveException (std::string msg) : msg_(msg) {}   
        std::string msg() const { return msg_; }                //return error message
    private:
        std::string msg_;
    };
    StrategyHuman ( Player* p);                                 //public constructor
    Command takeTurn ( std::vector<Card>& playableCards);       //implementation of virtual method takeTurn.  Player takes his turn and plays it.
};

#endif
