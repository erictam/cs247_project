#include <iostream>
#include "Player.h"

Player::Player (std::vector <Card> cards) : hand_(cards) {}

void Player::printHand() {
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        std::cout<<hand_[i]<<std::endl;
    }
}

void Player::getPlayableCards () {
}
