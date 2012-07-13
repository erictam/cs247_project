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
}

//method to determine the player holding the SEVEN SPADES card, who will go first
void Game::determineFirstPlayer () {
    currentPlayer_ = deck_.findCardInDeck (Card( (Suit)SPADE, (Rank)SEVEN) ) / 13 + 1;
    std::cout<<"A new round begins. It's player "<<currentPlayer_<<"'s turn to play."<<std::endl;
}


// Returns the score of the current player. Note that player is from 0 to 3.
int Game::getScore(int player) const {
    return playerScores_[player];
}

// Returns a pointer to an array of player scores
int const* Game::getScores() const {
    return playerScores_;
}

// Returns the number of discards for the player for the round.
// Note that player is from 0 to 3.
int Game::getDiscard (int player) {
    return getDiscarded(player).size();
}

// Returns all discarded cards for a player. Note that player is from 0 to 3.
std::vector<Card> Game::getDiscarded(int player) {
    // Only get the Cards if the player is not NULL
    if (players_[player])
        return players_[player]->getDiscarded();

    std::vector<Card> emptyVector;
    return emptyVector; 
}

// Returns the cards in a player's hand, if player has been initialized.
// Note that player is from 0 to 3.
std::vector<Card> Game::getHand(int player) {
    if (players_[player])
        return players_[player]->getHand();

    std::vector<Card> emptyVector;
    return emptyVector; 
}

// Returns a pointer to an array of booleans, signifying which cards have been played.
bool const* Game::getTable() const {
    return table_.getTable();
}

// Returns the current player whose turn it is, from 1 to 4, or 0 if no game is running.
int Game::getCurrentPlayer() const {
    return currentPlayer_;
}

// Checks if the current player is a human or computer player.
bool Game::getCurrentPlayerType() const {
    return players_[currentPlayer_ - 1]->getIsHuman();
}

// Ends the current game.
void Game::endGame() {
    // Sets the number of turns and the current player to zero.
    currentTurn_ = 0;
    currentPlayer_ = 0;
    // Clears the table of cards played.
    table_.clearTable();
    // Sets all four player's scores to zero and resets their hand
    for (int i = 0; i < NUM_PLAYERS; i++) {
        playerScores_[i] = 0;
        if (players_[i])
            players_[i]->clearPlayer();
    }

    state_ = QUITGAME;

    notify();
}

// Returns the current game state.
GameState Game::getCurrentState() const {
    return state_;
}

int Game::getWinner() const {
    int winner = 0;

    //find out who the winner is
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (playerScores_[i] < playerScores_[winner])
            winner = i;
    }
    return winner;
}

// Create and set each player's strategy, along with the random seed, before the deck
// is shuffled.
void Game::setPlayers(std::string playerTypes[], int seed) {
    for (int i = 1; i <= NUM_PLAYERS; i++) {
        //table_ will link the new player to the table
        //strategy determines the type of player; human or computer
        //deck_ will link the new player to the deck (required only because of the deck command)
        players_[i-1] = new Player(table_, playerTypes[i - 1], deck_);

        //set the players' score to 0 initially
        playerScores_[i-1] = 0;
    }

    // Set the seed.
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
    for (int i = 0; i < NUM_PLAYERS; i++) {
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

// Starts the game.
void Game::startGame() {
    // Set the current turn number to one and shuffle the deck.
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

    autoTurn();                 // Wait for computer players to take their turns
    state_ = TAKETURN;          // Set state for human to take their turn
    checkForRoundComplete();    // Check to see if the computers have completed the game

    notify();                   // Update view.
}

// Attempts to play a card
void Game::tryPlayingCard(int cardClicked) {
    // Do not allow other game states to play a card
    if (getCurrentState() != TAKETURN) {
        return;
    }

    // Grab the card in the hand that was selected.
    std::vector<Card> hand = players_[currentPlayer_ - 1]->getHand();
    Card c = hand[cardClicked];

    // If the card can be played, move to the next player and increment
    // the turn count.
    if (players_[currentPlayer_ - 1]->playCard(c)) {
        currentPlayer_++;
        if (currentPlayer_ == NUM_PLAYERS + 1) 
            currentPlayer_ = 1;
        currentTurn_++;
    }
    // If the card is invalid, return.
    else {
        return;
    }

    // Wait for computer players and check for completed rounds due to them
    autoTurn();
    state_ = TAKETURN;
    checkForRoundComplete();

    notify();   // Update view.
}

// Attempt to discard a card
void Game::tryDiscardingCard(int cardClicked) {
    // Only allow humans to discard a card, during a valid game state.
    if (getCurrentState() != TAKETURN) {
        return;
    }

    // Grab the selected card from the hand
    std::vector<Card> hand = players_[currentPlayer_ - 1]->getHand();
    Card c = hand[cardClicked];

    // If the card can be discarded...
    if (players_[currentPlayer_ - 1]->discardCard(c)) {
        // Add the rank of the card to the player's score
        // getRank() would return 0 for ACE etc.
        playerScores_[currentPlayer_ - 1] += (int)c.getRank() + 1;
        
        // Switch to the next player and turn.
        currentPlayer_++;
        if (currentPlayer_ == NUM_PLAYERS + 1) 
            currentPlayer_ = 1;
        currentTurn_++;
    }
    else {
        return;
    }

    // Wait for computer players
    autoTurn();
    checkForRoundComplete();

    notify();   // Update view.
}

// Rage quits
void Game::rageQuit( int player) {
    // Change the strategy to computer for the player
    players_[player]->rageQuit();

    // Let computers take their turn
    autoTurn();
    state_ = TAKETURN;
    checkForRoundComplete();

    notify();   // Update view
}

// Returns the current turn number
int Game::getCurrentTurn() const {
    return currentTurn_;
}


