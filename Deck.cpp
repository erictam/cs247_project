#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include "Deck.h"

const int CARD_COUNT = 52;

//public constructor
Deck::Deck () {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            //create one of every card and add to vector
            cards_.push_back( Card((Suit)i, (Rank)j) );
        }
    }
}

//method to print out entire deck
void Deck::printDeck () {
    for (int i = 0; (unsigned)i < cards_.size(); i++) {
        //print out each card
        std::cout<<cards_[i]<<" ";
        if (i % 13 == 12) {
            //start printing on a new line for next player's hand
            std::cout<<std::endl;
        }
    }
}

//method to shuffle contents of deck
void Deck::shuffle(){
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
        // save card in slot n temporarily during the swap
		Card c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

//method to deal cards to the player
std::vector<Card> Deck::deal(int player) {
    std::vector<Card> returnVector;
    // player is an int from 1 to 4, where i is the indices in the deck that
    // contains each player's cards
    for (int i = (player - 1) * 13 ; i < player * 13; i++) {
        //push the 13 cards that will make up the player's hand
        returnVector.push_back(cards_[i]);
    }
    return returnVector;
}

//method to find the position of a card in deck
int Deck::findCardInDeck (Card c) {
    for (int i = 0; i < CARD_COUNT; i++) {
        if (cards_[i] == c ) {
            return i;
        }
    }
    return 0;
}
