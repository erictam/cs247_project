#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <vector>
#include "Card.h"

class Deck {
public:
    Deck ();                                    //public constructor
    void printDeck () const;                    //method to print out entire deck
    void shuffle ();                            //method to shuffle contents of deck
    std::vector <Card> deal (int player) const; //method to deal cards to the player
    int findCardInDeck (Card c) const;          //method to find the position of a card in deck
private:
    std::vector <Card> cards_;
};


#endif
