#include <assert.h>
#include <iostream>
#include "Game.h"

Game::Game() {
    std::string input;
    for (int i = 1; i <= 4; i++) {
        std::cout<<"Is player "<<i<<" a human(h) or a computer(c)?\n>";
        std::cin>>input;
        assert (input == "c" || input == "C" || input == "H" || input == "h");
        
        std::vector<Card> hand = deck_.deal(i);

        if (input == "h" || input == "H") {
            players_[i-1] = new PlayerHuman(hand);
        }
        else if (input == "c" || input == "C") {
            players_[i-1] = new PlayerComputer(hand);
        }
    }
}

void Game::printPlayerHand (int p) {
    assert (1 <= p && p <= 4);
    players_[p - 1]->printHand();;
}

void Game::takeTurn () {
    Command c;
    std::cout<<">";
    std::cin>>c;
    if (c.type == QUIT) {
        exit(1);
    }
    else if (c.type == DECK) {
        printDeck(); 
            
    }
}

void Game::determineFirstPlayer () {
    currentPlayer_ = deck_.findCardInDeck (Card( (Suit)SPADE, (Rank)SEVEN) ) / 13 + 1;
    std::cout<<"A new round begins. It's player "<<currentPlayer_<<"'s turn to play."<<std::endl;
}
