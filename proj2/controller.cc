/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "controller.h"
#include <iostream>


Controller::Controller(Game *game) : game_(game) {}


void Controller::newGameButtonClicked() {
    game_->newGame();
} 

void Controller::endGameButtonClicked() {
    game_->endGame();
}

void Controller::resetButtonClicked() {
    //game_->resetCards();
} 

void Controller::setPlayers(std::string playerTypes[], int seed) {
    game_->setPlayers(playerTypes, seed);
}

void Controller::tryPlayingCard(Card c) {
    game_->tryPlayingCard(c); 
}

void Controller::tryDiscardingCard(Card c) {
    game_->tryDiscardingCard(c);
}
