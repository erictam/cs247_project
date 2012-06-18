#include <stdlib.h>
#include <iostream>
#include "Player.h"

class PlayerHuman : public Player {
public:    
    PlayerHuman ( Table& table );
    Command takeTurn ( std::vector<Card> playableCards);
    bool playCard (Card c, std::vector<Card> playableCards); 
};
