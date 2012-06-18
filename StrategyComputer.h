#ifndef _STRATEGYCOMPUTER_
#define _STRATEGYCOMPUTER_

#include "Strategy.h"

class StrategyComputer : public Strategy {
public:
    StrategyComputer (Player* p);
    Command takeTurn ( std::vector<Card> playableCards);
};

#endif
