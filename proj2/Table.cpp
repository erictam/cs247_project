#include <iostream>
#include <string>
#include "Table.h"

//public constructor
Table::Table () {
    //table is initially empty of cards
    clearTable(); 
}

//method to add new card to table
void Table::addCardToTable (Card c) {
    Suit suit = c.getSuit();
    Rank rank = c.getRank();
    
    //set the boolean to true to represent that the card is on the table
    cardsInPlay_[suit * 13 + rank] = true;
}

//method to check if card can be played next
bool Table::isLegalCard (Card c) const {
    Suit suit = c.getSuit();
    Rank rank = c.getRank();

    //if 7S has not yet been played, only 7S can be played
    if (!cardsInPlay_[SPADE * 13 + SEVEN]) {
        if (rank == (Rank)SEVEN && suit == (Suit)SPADE) {
            return true;
        }
        return false;
    }

    //if 7S has been played, other 7's can always be played
    if (rank == (Rank)SEVEN) {
        return true;
    }

    Rank rankAbove = (Rank)(rank + 1);
    Rank rankBelow = (Rank)(rank - 1);

    if (rank == (Rank)KING) {
        rankAbove = (Rank)(rank - 1);
    }
    else if (rank == (Rank)ACE) {
        rankBelow = (Rank)(rank + 1);
    }
    
    //if a card with matching suit, and rank above or rank below has been played, this card can be played
    return cardsInPlay_[suit * 13 + rankAbove] || cardsInPlay_[suit * 13 +rankBelow];
}

//method to clear the table of cards
void Table::clearTable () {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            //initially, no cards are on table
            cardsInPlay_[i * 13 + j] = false;
        }
    }
}

bool const* Table::getTable() const {
    return cardsInPlay_;
}
