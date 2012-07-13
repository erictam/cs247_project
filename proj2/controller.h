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


#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H


#include <gtkmm.h>
#include <string>
#include "Game.h"

class Game;

class Controller {
public:
   Controller( Game* );
   void newGameButtonClicked();
   void endGameButtonClicked();
   void resetButtonClicked();
   void setPlayers(std::string[], int);
   void tryPlayingCard(Card);
   void tryDiscardingCard(Card);
private:
   Game* game_;
}; // Controller


#endif

