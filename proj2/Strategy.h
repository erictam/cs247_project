#ifndef _STRATEGY_
#define _STRATEGY_

#include "Player.h"

class Strategy {
public:
    Strategy (Player* p);                                               //public constructor
    virtual Command takeTurn ( std::vector<Card>& playableCards) = 0;   //pure virtual method which will be implemented in strategyHuman and strategyComputer
protected:
    Player* p_;
};

#endif
