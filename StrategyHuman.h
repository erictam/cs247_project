#ifndef _STRATEGYHUMAN_
#define _STRATEGYHUMAN_

#include "Strategy.h"

class StrategyHuman : public Strategy {
public:
    StrategyHuman ( Player* p);
    ~StrategyHuman ();
    Command takeTurn ( std::vector<Card> playableCards);
};

#endif
