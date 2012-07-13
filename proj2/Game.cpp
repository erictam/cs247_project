#include <assert.h>
#include <iostream>
#include "Game.h"

const int NUM_PLAYERS = 4;
const int CARD_COUNT = 52;
const int MAX_SCORE = 80;

//public constructor
Game::Game() : currentPlayer_(0), currentTurn_(0) {
    table_ = Table();
    std::string strategy = "";
    /*for (int i = 1; i <= NUM_PLAYERS; i++) {
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
    }*/

    for (int i = 1; i <= NUM_PLAYERS; i++) {
        playerScores_[i - 1] = 0;
        players_[i - 1] = NULL;
    }
}

//public destructor
Game::~Game() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        //delete each of the players
        delete players_[i];
    }
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
        playerScores_[currentPlayer_ - 1] += (int)c.card.getRank() + 1;
    }
    else if (c.type == RAGEQUIT) {
        std::cout<<"Player "<<currentPlayer_<<" ragequits. A computer will now take over."<<std::endl;
        return;
    }

    //increment the currentTurn_.  It starts at 1, and goes to 52.
    currentTurn_++;



    //increment currentPlayer_ and loop back to 1st player.

}

//method to determine the player holding the SEVEN SPADES card, who will go first
void Game::determineFirstPlayer () {
    currentPlayer_ = deck_.findCardInDeck (Card( (Suit)SPADE, (Rank)SEVEN) ) / 13 + 1;
    std::cout<<"A new round begins. It's player "<<currentPlayer_<<"'s turn to play."<<std::endl;
}


//int player parameter passed in from 0 to 3
int Game::getScore(int player) const {
    return playerScores_[player];
}

int const* Game::getScores() const {
    return playerScores_;
}

int Game::getDiscard (int player) {
    return getDiscarded(player).size();
}

//int player parameter passed in from 0 to 3
std::vector<Card> Game::getDiscarded(int player) {
    if (players_[player])
        return players_[player]->getDiscarded();

    std::vector<Card> emptyVector;
    return emptyVector; 
}

//int player parameter passed in from 0 to 3
std::vector<Card> Game::getHand(int player) {
    if (players_[player])
        return players_[player]->getHand();

    std::vector<Card> emptyVector;
    return emptyVector; 
}

bool const* Game::getTable() const {
    return table_.getTable();
}

//Returns player 1 to 4
int Game::getCurrentPlayer() const {
    return currentPlayer_;
}

bool Game::getCurrentPlayerType() const {
    return players_[currentPlayer_ - 1]->getIsHuman();
}

void Game::endGame() {
    currentTurn_ = 0;
    currentPlayer_ = 0;
    table_.clearTable();
    for (int i = 0; i < 4; i++) {
        playerScores_[i] = 0;
        if (players_[i])
            players_[i]->clearPlayer();
    }
    state_ = QUITGAME;
    notify();
}

GameState Game::getCurrentState() const {
    return state_;
}

void Game::setPlayers(std::string playerTypes[], int seed) {
    for (int i = 1; i <= NUM_PLAYERS; i++) {
        //table_ will link the new player to the table
        //strategy determines the type of player; human or computer
        //deck_ will link the new player to the deck (required only because of the deck command)
        players_[i-1] = new Player(table_, playerTypes[i - 1], deck_);

        //set the players' score to 0 initially
        playerScores_[i-1] = 0;
    }

    srand48(seed);
}

// Lets the computer take their turns
void Game::autoTurn() {
    // While the current player is not human...
    while (!getCurrentPlayerType() && currentTurn_ <= CARD_COUNT) {
        takeTurn();
        // Increment and mod the result such that it returns 1 to 4
        currentPlayer_++;
        currentPlayer_ = (currentPlayer_ - 1) % NUM_PLAYERS + 1;
    }
}

// Checks to see if the round or game is complete
void Game::checkForRoundComplete() {
    bool gameIsComplete = false;

    // Checks each player's score for any over MAX_SCORE
    for (int i = 0; i < 4; i++) {
        if (playerScores_[i] >= MAX_SCORE) {
            gameIsComplete = true;
        }
    }

    // If all cards have been played, change the state to
    // Finished Game or Next Round depending on the boolean
    if (currentTurn_ > CARD_COUNT) {
        if (gameIsComplete) {
            state_ = FINISHEDGAME;
        }
        else {
            state_ = NEXTROUND;
        }
    }
}

void Game::startGame() {
    currentTurn_ = 1;
    deck_.shuffle();

    //clear the table of any cards on it
    table_.clearTable();

    //clear each player of their hand and discarded pile, and deal a new hand to each player
    for (int i = 1; i <= NUM_PLAYERS; i++) {
        if (players_[i-1]) {
            players_[i-1]->clearPlayer();
            std::vector<Card> hand = deck_.deal(i);
            players_[i-1]->assignHand(hand);
        }
    }

    //figure out the first player and set currentPlayer_.
    determineFirstPlayer();

    autoTurn();
    state_ = TAKETURN;
    checkForRoundComplete();

    notify();
}

void Game::tryPlayingCard(int cardClicked) {
    if (getCurrentState() != TAKETURN) {
        return;
    }

    std::vector<Card> hand = players_[currentPlayer_ - 1]->getHand();
    Card c = hand[cardClicked];

    if (players_[currentPlayer_ - 1]->playCard(c)) {
        currentPlayer_++;
        if (currentPlayer_ == NUM_PLAYERS + 1) 
            currentPlayer_ = 1;
        currentTurn_++;
    }
    else {
        return;
    }

    autoTurn();
    state_ = TAKETURN;
    checkForRoundComplete();

    notify();
}

void Game::tryDiscardingCard(int cardClicked) {
    if (getCurrentState() != TAKETURN) {
        return;
    }

    std::vector<Card> hand = players_[currentPlayer_ - 1]->getHand();
    Card c = hand[cardClicked];

    if (players_[currentPlayer_ - 1]->discardCard(c)) {
        playerScores_[currentPlayer_ - 1] += (int)c.getRank() + 1;
        currentPlayer_++;
        if (currentPlayer_ == NUM_PLAYERS + 1) 
            currentPlayer_ = 1;
        currentTurn_++;
    }
    else {
        return;
    }

    autoTurn();
    checkForRoundComplete();

    notify();
}

void Game::rageQuit( int player) {
    players_[player]->rageQuit();

    autoTurn();
    state_ = TAKETURN;
    checkForRoundComplete();

    notify();
}

int Game::getCurrentTurn() const {
    return currentTurn_;
}


