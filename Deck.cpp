#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include "Deck.h"

const int CARD_COUNT = 52;

Deck::Deck () {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            cards_.push_back( Card((Suit)i, (Rank)j) );
        }
    }
}

void Deck::printDeck () {
    for (int i = 0; (unsigned)i < cards_.size(); i++) {
        std::cout<<cards_[i]<<" ";
        if (i % 13 == 12) {
            std::cout<<std::endl;
        }
    }
}

void Deck::shuffle(){
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

std::vector<Card> Deck::deal(int player) {
    std::vector<Card> returnVector;
    for (int i = (player - 1) * 13 ; i < player * 13; i++) {
        returnVector.push_back(cards_[i]);
    }
    return returnVector;
}

int Deck::findCardInDeck (Card c) {
    for (int i = 0; i < 52; i++) {
        if (cards_[i] == c ) {
            return i;
        }
    }
    return 0;
}
