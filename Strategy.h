#ifndef _STRATEGY_
#define _STRATEGY_

#include "Player.h"

class Player;

class Strategy {
public:
    Strategy (Player* p);
    ~Strategy ();
    virtual Command takeTurn ( std::vector<Card> playableCards) = 0;
protected:
    Player* p_;
};

#endif
