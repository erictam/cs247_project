#include <assert.h>
#include <iostream>
#include "Game.h"

const int NUM_PLAYERS = 4;
const int CARD_COUNT = 52;
const int MAX_SCORE = 80;

//public constructor
Game::Game() : currentPlayer_(0), currentTurn_(1) {
    table_ = Table();
    std::string strategy = "";
    for (int i = 1; i <= NUM_PLAYERS; i++) {
        //create 4 new players
        std::cout<<"Is player "<<i<<" a human(h) or a computer(c)?\n>";
        std::cin>>strategy;
        assert (strategy == "c" || strategy == "C" || strategy == "H" || strategy == "h");

        //table_ will link the new player to the table
        //strategy determines the type of player; human or computer
        //deck_ will link the new player to the deck (required only because of the deck command)
        players_[i-1] = new Player(table_, strategy, deck_);
        
        //set the players' score to 0 initially
        playerScores_[i-1] = 0;
    }
}

//public destructor
Game::~Game() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        //delete each of the players
        delete players_[i];
    }
}

//method to print player p's hand
void Game::printPlayerHand (int p) const {
    assert (1 <= p && p <= NUM_PLAYERS);
    std::cout<<"Player "<< p <<"'s hand : ";
    players_[p - 1]->printHand();;
}

//method to go through one player's turn
void Game::takeTurn () {
    //get the current player to take his turn
    //get the command the player made
    Command c = players_[currentPlayer_ - 1]->takeTurn();

    if (c.type == QUIT) {
        // throw QuitException if quitting the game
        throw QuitException();
    }
    else if (c.type == DECK) {
        return;
    }
    else if (c.type == PLAY) {
        std::cout<<"Player "<<currentPlayer_<<" plays "<<c.card<<"."<<std::endl;;
    }
    else if (c.type == DISCARD) {
        std::cout<<"Player "<<currentPlayer_<<" discards "<<c.card<<"."<<std::endl;
    }
    else if (c.type == RAGEQUIT) {
        std::cout<<"Player "<<currentPlayer_<<" ragequits. A computer will now take over."<<std::endl;
        return;
    }

    //increment the currentTurn_.  It starts at 1, and goes to 52.
    currentTurn_++;

    //increment currentPlayer_ and loop back to 1st player.
    currentPlayer_++;
    if (currentPlayer_ == NUM_PLAYERS + 1) {
        currentPlayer_ = 1;
    }
}

//method to determine the player holding the SEVEN SPADES card, who will go first
void Game::determineFirstPlayer () {
    currentPlayer_ = deck_.findCardInDeck (Card( (Suit)SPADE, (Rank)SEVEN) ) / 13 + 1;
    std::cout<<"A new round begins. It's player "<<currentPlayer_<<"'s turn to play."<<std::endl;
}

//method to print current cards on the table
void Game::printTable () const {
    std::cout<<"Cards on the table:"<<std::endl;
    table_.printTable();
}

//method to start the game
void Game::run () {
    bool gameIsComplete = false;

    //loop until game is finished (any player has a score of 80+)
    while (gameIsComplete == false) {
        //restart game so set currentTurn_ to 1 and shuffle deck
        currentTurn_ = 1;
        deck_.shuffle();

        //clear the table of any cards on it
        table_.clearTable();

        //clear each player of their hand and discarded pile, and deal a new hand to each player
        for (int i = 1; i <= NUM_PLAYERS; i++) {
            players_[i-1]->clearPlayer();
            std::vector<Card> hand = deck_.deal(i);
            players_[i-1]->assignHand(hand);
        }

        //figure out the first player and set currentPlayer_.
        determineFirstPlayer();

        //we will always have 52 turns in one round.
        //so takeTurn 52 times
        while (currentTurn_ <= CARD_COUNT) {
            try {
                takeTurn();
            }
            catch (QuitException& err ) {
                //if we enter here, quit command was input
                return;
            }
        }

        //this will hold the score of a player from the most recent round
        int score;

        //this will hold the discard pile of the player
        std::vector<Card> discarded;

        for (int i = 1; i <= NUM_PLAYERS; i++) {
            //get discarded pile
            discarded = players_[i-1]->getDiscarded();

            //get score from recent round
            score = players_[i-1]->getScore();

            //print out discards
            std::cout<<"Player "<<i<<"'s discards:";
            for (int j = 0; (unsigned)j < discarded.size(); j++) {
                std::cout<<" "<<discarded[j];
            }
            std::cout<<std::endl;

            //print out score
            std::cout<<"Player "<<i<<"'s score: "<<playerScores_[i-1]<<" + "<<score<<" = "<<playerScores_[i-1] + score<<std::endl;

            //increment score accordingly
            playerScores_[i-1] += score;

            //game is finished ONLY if someone has a score of 80+ (max score)
            if (playerScores_[i-1] >= MAX_SCORE) {
                gameIsComplete = true;
            }
        }
    }

    //figure out who the winner and print a message about the winner
    int winner = 0;
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (playerScores_[i] < playerScores_[winner]) {
            winner = i;
        }
    }

    std::cout<<"Player "<<winner + 1<<" wins!"<<std::endl;

}
