#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <vector>
#include "Card.h"

class Deck {
public:
    Deck ();
    void printDeck ();
    void shuffle ();
    std::vector <Card> deal (int);
    int findCardInDeck (Card c);
private:
    std::vector <Card> cards_;
};


#endif
