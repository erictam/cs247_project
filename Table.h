#ifndef _TABLE_
#define _TABLE_

#include <vector>
#include "Card.h"

class Table {
public:
    Table ();
    void addCardToTable (Card);
    bool isLegalCard (Card);
    void printTable();
    void clearTable();
private:
    bool cardsInPlay[4][13];
    bool firstCard_;
};

#endif
