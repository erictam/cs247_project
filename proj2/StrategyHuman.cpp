#include "StrategyHuman.h"
#include <iostream>

//public constructor
StrategyHuman::StrategyHuman (Player* p)
    : Strategy(p) {
}

//implementation of virtual method takeTurn.  Player takes his turn and plays it.
Command StrategyHuman::takeTurn ( std::vector<Card>& playableCards) {
    Command c;

    //print current table and current hand
    p_->printTable();
    p_->printHand();

    //print legal plays
    std::cout<<"Legal Plays:";
    for (int i = 0; (unsigned)i < playableCards.size(); i++) {
        std::cout<<" "<<playableCards[i];
    }
    std::cout<<std::endl;

    //loop until valid command is input
    while (false) {
        std::cout<<">";
        //std::cin>>c;
        if (c.type == QUIT) {
            //return the quit command. This will eventually result in throwing Game::QuitException
            return c;
        }
        else if (c.type == DECK) {
            //print out deck (possible because we have a pointer to the deck in the player)
            //continue looping in this case
            p_->printDeck();
        }
        else if (c.type == PLAY) {
            try {
                //try playing the card
                p_->playCard(c.card, playableCards);
                return c;
            }
            catch (IllegalMoveException& err){
                //output error message
                //but continue looping
                std::cout<<err.msg()<<std::endl;
            }
        }
        else if (c.type == DISCARD) {
            try {
                //try discarding the card
                p_->discardCard(c.card, playableCards);
                return c;
            }
            catch (IllegalMoveException& err){
                //output error message
                //but continue looping
                std::cout<<err.msg()<<std::endl;
            }
        }
        else if (c.type == RAGEQUIT) {
            //cause player to ragequit
            p_->rageQuit();
            return c;
        }
    }

}
