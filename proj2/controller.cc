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
#include "Game.h"


Controller::Controller(Game *game) : game_(game) {}


void Controller::newGameButtonClicked() {
     game_->newGame();
} 


void Controller::resetButtonClicked() {
     //game_->resetCards();
} 

void Controller::setPlayers(std::string playerTypes[]) {
    game_->setPlayers(playerTypes);
}
