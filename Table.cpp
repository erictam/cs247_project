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
    cardsInPlay_[suit][rank] = true;
}

//method to check if card can be played next
bool Table::isLegalCard (Card c) const {
    Suit suit = c.getSuit();
    Rank rank = c.getRank();

    //if 7S has not yet been played, only 7S can be played
    if (!cardsInPlay_[SPADE][SEVEN]) {
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
    return cardsInPlay_[suit][rankAbove] || cardsInPlay_[suit][rankBelow];
}

//method to print current cards on table
void Table::printTable () const {
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < SUIT_COUNT; i++) {
        if (i == 0) {
            std::cout<<"Clubs:";
        }
        else if (i == 1) {
            std::cout<<"Diamonds:";
        }
        else if (i == 2) {
            std::cout<<"Hearts:";
        }
        else if (i == 3) {
            std::cout<<"Spades:";
        }
        for (int j = 0; j < RANK_COUNT; j++) {
            // output the card rank if it is on the table
            if (cardsInPlay_[i][j]) {
                std::cout<<" "<<ranks[j];
            }
        }
        std::cout<<std::endl;
    }
}

//method to clear the table of cards
void Table::clearTable () {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            //initially, no cards are on table
            cardsInPlay_[i][j] = false;
        }
    }
}
