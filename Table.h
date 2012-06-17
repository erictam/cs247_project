#ifndef _TABLE_
#define _TABLE_

#include <vector>
#include "Card.h"

class Table {
public:
    bool isLegalCard (Card c);
private:
    std::vector <Card> cards_;
};

#endif
