#include "controller.h"
#include <iostream>

// Constructor for controller. Links to Model Game class.
Controller::Controller(Game *game) : game_(game) {}

// Calls start game when the new game button is clicked.
void Controller::newGameButtonClicked() {
    game_->startGame();
} 

// Calls end game when the end game button is clicked.
void Controller::endGameButtonClicked() {
    game_->endGame();
}

// Calls the model to set the player types (human or computer), along with
// the random seed
void Controller::setPlayers(std::string playerTypes[], int seed) {
    game_->setPlayers(playerTypes, seed);
}

// Attempts to play a card
void Controller::tryPlayingCard(Card c) {
    game_->tryPlayingCard(c); 
}

// Attempts to discard a card
void Controller::tryDiscardingCard(Card c) {
    game_->tryDiscardingCard(c);
}
