#include <iostream>
#include "Player.h"
#include "StrategyHuman.h"
#include "StrategyComputer.h"

Player::Player ( Table& table, std::string strategy) 
    : currentTable_(&table) {
    if (strategy == "h" || strategy == "H") {
        currentStrategy_ = new StrategyHuman(this);
    }
    else if (strategy == "c" || strategy == "C") {
        currentStrategy_ = new StrategyComputer(this);
    }
}

Player::~Player () {
    if (currentStrategy_ != NULL) {
        delete currentStrategy_;
    }
}

void Player::printHand() {
    std::cout<<"Your hand:";
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        std::cout<<" "<<hand_[i];
    }
    std::cout<<std::endl;
}

std::vector<Card> Player::getPlayableCards () {
    std::vector<Card> playableCards;
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        if (currentTable_->isLegalCard(hand_[i])) {
            playableCards.push_back(hand_[i]);
        }
    }
    return playableCards;
}

void Player::removeCardInHand (Card c) {
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        if (hand_[i] == c) {
            hand_.erase(hand_.begin() + i);
        }
    }
}

void Player::discardCard (Card c, std::vector<Card> playableCards) {
    if (playableCards.size() != 0) {
        throw StrategyHuman::IllegalMoveException("You have a legal play. You may not discard.");
    }
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        if (c == hand_[i]) {
            discarded_.push_back(c);    
            removeCardInHand( c );
            return; 
        }
    }
    throw StrategyHuman::IllegalMoveException("You do not hold the card. You may not discard it.");
}

int Player::getScore () {
    int score = 0;
    for (int i = 0; (unsigned)i < discarded_.size(); i++) {
        score += (int)discarded_[i].getRank() + 1;
    }
    return score;
}

std::vector<Card> Player::getDiscarded() {
    return discarded_;
}

void Player::clearPlayer () {
    hand_.clear();
    discarded_.clear();
}

void Player::assignHand (std::vector<Card> cards) {
    hand_ = cards;
}

void Player::printTable () {
    std::cout<<"Cards on the table:"<<std::endl;
    currentTable_->printTable();
}

void Player::playCard (Card c, std::vector<Card> playableCards) {
    for (int i = 0; (unsigned)i < playableCards.size(); i++) {
        if (c == playableCards[i]) {
            currentTable_->addCardToTable( c );
            removeCardInHand( c ); 
            return;
        }
    }
    throw StrategyHuman::IllegalMoveException("This is not a legal play.");
}

Command Player::takeTurn (std::vector<Card> playableCards) {
    Command c = currentStrategy_->takeTurn( playableCards);
    return c;
}

void Player::rageQuit () {
    Strategy* temp = currentStrategy_;
    currentStrategy_ = new StrategyComputer(this);
    delete temp;
}
