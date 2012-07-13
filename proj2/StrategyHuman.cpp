#include "StrategyHuman.h"
#include <iostream>

//public constructor
StrategyHuman::StrategyHuman (Player* p)
    : Strategy(p) {
}

//implementation of virtual method takeTurn.  Player takes his turn and plays it.
Command StrategyHuman::takeTurn ( std::vector<Card>& playableCards) {
    Command c;
    return c;
}
