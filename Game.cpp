#include <assert.h>
#include <iostream>
#include "Game.h"

Game::Game() : currentPlayer_(0), currentTurn_(1) {
    table_ = Table();
    std::string input;
    for (int i = 1; i <= 4; i++) {
        std::cout<<"Is player "<<i<<" a human(h) or a computer(c)?\n>";
        std::cin>>input;
        assert (input == "c" || input == "C" || input == "H" || input == "h");

        if (input == "h" || input == "H") {
            players_[i-1] = new PlayerHuman( table_);
        }
        else if (input == "c" || input == "C") {
            players_[i-1] = new PlayerComputer( table_);
        }

        playerScores[i-1] = 0;
    }
}

void Game::printPlayerHand (int p) {
    assert (1 <= p && p <= 4);
    std::cout<<"Player "<< p <<"'s hand : ";
    //std::cout<<"Your hand:";
    players_[p - 1]->printHand();;
}

void Game::takeTurn () {
    std::vector<Card> playableCards = players_[currentPlayer_ - 1]->getPlayableCards();
    
    Command c = players_[currentPlayer_ - 1]->takeTurn(playableCards);

    if (c.type == QUIT) {
        exit(1);
    }
    else if (c.type == DECK) {
        printDeck(); 
    }
    else if (c.type == PLAY) {
        std::cout<<"Player "<<currentPlayer_<<" plays "<<c.card<<"."<<std::endl;;
    }
    else if (c.type == DISCARD) {
        std::cout<<"Player "<<currentPlayer_<<" discards "<<c.card<<"."<<std::endl;
    }

    currentPlayer_++;
    if (currentPlayer_ == 5) {
        currentPlayer_ = 1;
    }
}

void Game::determineFirstPlayer () {
    currentPlayer_ = deck_.findCardInDeck (Card( (Suit)SPADE, (Rank)SEVEN) ) / 13 + 1;
    std::cout<<"A new round begins. It's player "<<currentPlayer_<<"'s turn to play."<<std::endl;
}

void Game::printTable () {
    std::cout<<"Cards on the table:"<<std::endl;
    table_.printTable();
}

void Game::run () {
    bool gameIsComplete = false;
    while (gameIsComplete == false) {
        currentTurn_ = 1;
        deck_.shuffle();

        table_.clearTable();
        for (int i = 1; i <= 4; i++) {
            players_[i-1]->clearPlayer();
            std::vector<Card> hand = deck_.deal(i);
            players_[i-1]->assignHand(hand);
        }

        determineFirstPlayer();
        while (currentTurn_ <= 52) {
            takeTurn();
            currentTurn_++;
        }
        int score;
        std::vector<Card> discarded;
        for (int i = 1; i <= 4; i++) {
            discarded = players_[i-1]->getDiscarded();
            score = players_[i-1]->getScore();

            std::cout<<"Player "<<i<<"'s discards:";
            for (int j = 0; (unsigned)j < discarded.size(); j++) {
                std::cout<<" "<<discarded[j];
            }
            std::cout<<std::endl;

            std::cout<<"Player "<<i<<"'s score: "<<playerScores[i-1]<<" + "<<score<<" = "<<playerScores[i-1] + score<<std::endl;

            playerScores[i-1] += score;
            if (playerScores[i-1] >= 80) {
                gameIsComplete = true;
            }
        }
    }
    int winner = 0;
    for (int i = 1; i < 4; i++) {
        if (playerScores[i] < playerScores[winner]) {
            winner = i;
        }
    }

    std::cout<<"Player "<<winner + 1<<" wins!"<<std::endl;
    exit(1);
}
