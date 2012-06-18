#ifndef _STRATEGYCOMPUTER_
#define _STRATEGYCOMPUTER_

#include "Strategy.h"

class StrategyComputer : public Strategy {
public:
    StrategyComputer (Player* p);                                   //public constructor
    Command takeTurn ( std::vector<Card>& playableCards);           //implementation of virtual method takeTurn.  Player takes his turn and plays it.
};

#endif
