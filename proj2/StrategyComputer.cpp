#include "StrategyComputer.h"
#include <iostream>
#include <sstream>

//public constructor
StrategyComputer::StrategyComputer (Player* p)
    : Strategy(p) {
}

//implementation of virtual method takeTurn.  Player takes his turn and plays it.
Command StrategyComputer::takeTurn ( std::vector<Card>& playableCards) {
    std::string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};

    Command c;

    //command string will represent the usual user input
    std::string command = "";
    if (playableCards.size() != 0 ) {
        //build command string to play first playable card if we have playable cards
        command += "play ";
        command += ranks[playableCards[0].getRank()];
        command += suits[playableCards[0].getSuit()];

        //play the card
        p_->playCard (playableCards[0], playableCards);
    }
    else {
        //build command string to discard first card if we have no playable cards
        command += "discard " ;
        command += ranks[p_->hand_[0].getRank()];
        command += suits[p_->hand_[0].getSuit()];

        //discard the card
        p_->discardCard (p_->hand_[0], playableCards);
    }

    //convert the command string to a command object
    std::stringstream ss(command);
    //ss>>c;
    return c;
}
