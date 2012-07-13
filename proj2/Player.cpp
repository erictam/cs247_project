#include <iostream>
#include "Player.h"
#include "StrategyHuman.h"
#include "StrategyComputer.h"

//public constructor
Player::Player ( Table& table, std::string strategy, Deck& deck) 
    : currentTable_(&table), deck_(&deck) {
    //set the appropriate type of strategy
    if (strategy == "h" || strategy == "H") {
        currentStrategy_ = new StrategyHuman(this);
        isHuman_ = true;
    }
    else if (strategy == "c" || strategy == "C") {
        currentStrategy_ = new StrategyComputer(this);
        isHuman_ = false;
    }
}

//public destructor
Player::~Player () {
    if (currentStrategy_ != NULL) {
        //delete only the currentStrategy_
        //no need to delete currentTable_ because Game will delete for us
        delete currentStrategy_;
    }
}

//method to print the hand of the player
void Player::printHand() const {
    std::cout<<"Your hand:";
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        std::cout<<" "<<hand_[i];
    }
    std::cout<<std::endl;
}

std::vector<Card> Player::getHand () const {
    return hand_;
}

//method to get a list of playable cards in the player's hand
std::vector<Card> Player::getPlayableCards () const {
    std::vector<Card> playableCards;
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        //check if the card is a legal card based on the currentTable_
        if (currentTable_->isLegalCard(hand_[i])) {
            playableCards.push_back(hand_[i]);
        }
    }
    return playableCards;
}

//method to get player to take his turn
Command Player::takeTurn () {
    // get list of playable cards
    std::vector<Card> playableCards = getPlayableCards();

    printHand();
    for (unsigned int i = 0; i < playableCards.size(); i++) {
        std::cout<<playableCards[i]<<" ";
    }
    std::cout<<std::endl;
    
    //call the takeTurn method of the strategy
    Command c = currentStrategy_->takeTurn( playableCards );
    return c;
}

//method to get player to play a card onto table
void Player::playCard (Card c, std::vector<Card>& playableCards) {
    /*std::cout<<"Something";
    for (int i = 0; (unsigned)i < playableCards.size(); i++) {
        // add card to table of played cards if valid
        if (c == playableCards[i]) {

            //add the card to the table, and remove the card from your hand
            currentTable_->addCardToTable( c );
            removeCardInHand( c ); 

            return;
        }
    }
    //if the card is not a playable card, throw exception
    throw StrategyHuman::IllegalMoveException("This is not a legal play.");*/
}

bool Player::playCard (Card c) {
    //std::cout<<"Playing : "<<c<<std::endl;
    std::vector<Card> playableCards = getPlayableCards();
    for (int i = 0; (unsigned)i < playableCards.size(); i++) {
        // add card to table of played cards if valid
        if (c == playableCards[i]) {
            
            //add the card to the table, and remove the card from your hand
            currentTable_->addCardToTable( c );
            removeCardInHand( c ); 
            
            return true;
        }
    }
    return false;  
}

//method to get player to discard card into discard pile
void Player::discardCard (Card c, std::vector<Card>& playableCards) {
    if (playableCards.size() != 0) {
        throw StrategyHuman::IllegalMoveException("You have a legal play. You may not discard.");
    }
    for (int i = 0; (unsigned)i < hand_.size(); i++) {
        if (c == hand_[i]) {

            //add card to discarded pile, and remove the card from your hand
            discarded_.push_back(c);    
            removeCardInHand( c );
            return; 
        }
    }
    throw StrategyHuman::IllegalMoveException("You do not hold the card. You may not discard it.");
}

//method to get player to discard card into discard pile
bool Player::discardCard (Card c) {
    //std::cout<<"Discarding : "<<c<<std::endl;
    std::vector<Card> playableCards = getPlayableCards();
    if (playableCards.size() != 0) {
        //throw StrategyHuman::IllegalMoveException("You have a legal play. You may not discard.");
        return false;
    }
    for (unsigned int i = 0; i < hand_.size(); i++) {
        if (c == hand_[i]) {

            //add card to discarded pile, and remove the card from your hand
            discarded_.push_back(c);    
            removeCardInHand( c );
            return true; 
        }
    }
    //throw StrategyHuman::IllegalMoveException("You do not hold the card. You may not discard it.");
    return false;
}

//method to remove card from hand
void Player::removeCardInHand (Card c) {
    for (unsigned int i = 0; i < hand_.size(); i++) {
        if (hand_[i] == c) {
            hand_.erase(hand_.begin() + i);
        }
    }
}

//method to get score calculated based on discard pile
int Player::getScore () const {
    int score = 0;
    for (int i = 0; (unsigned)i < discarded_.size(); i++) {
        //sum up the ranks of each discarded card.  A = 1, J = 11, Q = 12, K = 13
        score += (int)discarded_[i].getRank() + 1;
    }
    return score;
}

//method to get list of discarded cards
std::vector<Card> Player::getDiscarded() const {
    return discarded_;
}

//method to clear player's hand, discard pile
void Player::clearPlayer () {
    hand_.clear();
    discarded_.clear();
}

//method to assign new hand to player
void Player::assignHand (std::vector<Card> cards) {
    hand_ = cards;
}

//method to print cards currently on table
void Player::printTable () const {
    std::cout<<"Cards on the table:"<<std::endl;
    currentTable_->printTable();
}

//method to get player to ragequit
void Player::rageQuit () {
    // set pointer to human strategy
    Strategy* temp = currentStrategy_;
    //change to computer strategy
    currentStrategy_ = new StrategyComputer(this);
    // delete human strategy associated with this player
    delete temp;

    isHuman_ = false;
}

//method to print the deck (only needed to deck command) 
void Player::printDeck() const {                                              
        deck_->printDeck();
}

bool Player::getIsHuman() const {
    return isHuman_;
}

