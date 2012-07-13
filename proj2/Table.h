#ifndef _TABLE_
#define _TABLE_

#include <vector>
#include "Card.h"

class Table {
public:
    Table ();                           //public constructor
    void addCardToTable (Card);         //method to add new card to table
    bool isLegalCard (Card) const;      //method to check if card can be played next
    void clearTable();                  //method to clear the table of cards
    bool const* getTable() const;
private:
    bool cardsInPlay_[52];
};

#endif
