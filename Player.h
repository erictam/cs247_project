#ifndef _PLAYER_
#define _PLAYER_

//#include "Hand.h"
#include <vector>
#include "Card.h"
#include "Command.h"

class Player {
public:
    Player (std::vector <Card> hand);
    void printHand ();
    void getPlayableCards();
    virtual void playCard () = 0;
protected:
    std::vector<Card> hand_;
    std::vector<Card> discarded_;
};

#endif
