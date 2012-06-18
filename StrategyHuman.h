#ifndef _STRATEGYHUMAN_
#define _STRATEGYHUMAN_

#include "Strategy.h"

class StrategyHuman : public Strategy {
public:
    class IllegalMoveException {
    public:
        IllegalMoveException (std::string msg) : msg_(msg) {}
        std::string msg() const { return msg_; }
    private:
        std::string msg_;
    };
    StrategyHuman ( Player* p);
    ~StrategyHuman ();
    Command takeTurn ( std::vector<Card> playableCards);
};

#endif
