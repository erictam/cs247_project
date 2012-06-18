#include <iostream>
#include <string>
#include "Table.h"

Table::Table () : firstCard_(true) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cardsInPlay[i][j] = false;
        }
    }
}

void Table::addCardToTable (Card c) {
    Suit suit = c.getSuit();
    Rank rank = c.getRank();

    cardsInPlay[suit][rank] = true;
}

bool Table::isLegalCard (Card c) {
    Suit suit = c.getSuit();
    Rank rank = c.getRank();
    if (!cardsInPlay[SPADE][SEVEN]) {
        if (rank == (Rank)SEVEN && suit == (Suit)SPADE) {
            return true;
        }
        return false;
    }
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
    
    return cardsInPlay[suit][rankAbove] || cardsInPlay[suit][rankBelow];
}

void Table::printTable () {
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < 4; i++) {
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
        for (int j = 0; j < 13; j++) {
            if (cardsInPlay[i][j]) {
                std::cout<<" "<<ranks[j];
            }
        }
        std::cout<<std::endl;
    }
}

void Table::clearTable () {
    firstCard_ = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cardsInPlay[i][j] = false;
        }
    }
}
