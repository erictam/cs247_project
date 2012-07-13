#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <gtkmm.h>
#include <string>
#include "Game.h"

class Game;

class Controller {
public:
   Controller( Game* );                     // Constructor
   void newGame();                          // Starts a new game
   void endGameButtonClicked();             // Ends a game
   void setPlayers(std::string[], int);     // Sets all player types and seed
   void tryPlayingCard(int);                // Attempts to play a card
   void tryDiscardingCard(int);             // Attempts to discard a card
   void rageQuit(int);                      // Changes a human player into a computer
private:
   Game* game_;                             // Model Game class
}; // Controller


#endif

