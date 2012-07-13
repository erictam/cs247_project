#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <gtkmm.h>
#include <string>
#include "Game.h"

class Game;

class Controller {
public:
   Controller( Game* );                     // Constructor
   void newGameButtonClicked();             // Starts a new game
   void endGameButtonClicked();             // Ends a game
   void setPlayers(std::string[], int);     // Sets all player types and seed
   void tryPlayingCard(Card);               // Attempts to play a card
   void tryDiscardingCard(Card);            // Attempts to discard a card

    bool const* getTable() const;
    int const* getScores() const;
    int getCurrentPlayer() const;
private:
   Game* game_;                             // Model Game class
}; // Controller


#endif

