#include "StrategyComputer.h"

StrategyComputer::StrategyComputer (Player& p)
    : Strategy(p) {
}

Command StrategyComputer::takeTurn ( std::vector<Card> playableCards) {
    std::string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    Command c;
    std::string command = "";
    if (playableCards.size() != 0 ) {
        command += "play ";
        command += ranks[playableCards[0].getRank()];
        command += suits[playableCards[0].getSuit()];
        playCard (playableCards[0], playableCards);
    }
    else {
        command += "discard " ;
        command += ranks[hand_[0].getRank()];
        command += suits[hand_[0].getSuit()];
        discardCard (hand_[0], playableCards);
    }
    std::stringstream ss(command);
    ss>>c;
    return c;
}
