#include "StrategyHuman.h"
#include <iostream>

StrategyHuman::StrategyHuman (Player* p)
    : Strategy(p) {
}

Command StrategyHuman::takeTurn ( std::vector<Card> playableCards) {
    Command c;
    p_->printTable();
    p_->printHand();

    std::cout<<"Legal Plays:";
    for (int i = 0; (unsigned)i < playableCards.size(); i++) {
        std::cout<<" "<<playableCards[i];
    }
    std::cout<<std::endl;

    while (true) {
        std::cout<<">";
        std::cin>>c;
        if (c.type == QUIT) {
            return c;
        }
        else if (c.type == DECK) {
            return c;
        }
        else if (c.type == PLAY) {
            try {
                p_->playCard(c.card, playableCards);
                return c;
            }
            catch (IllegalMoveException& err){
                std::cout<<err.msg()<<std::endl;
            }
        }
        else if (c.type == DISCARD) {
            try {
                p_->discardCard(c.card, playableCards);
                return c;
            }
            catch (IllegalMoveException& err){
                std::cout<<err.msg()<<std::endl;
            }
        }
        else if (c.type == RAGEQUIT) {
             p_->rageQuit();
            return c;
        }
    }

}
