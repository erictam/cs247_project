#ifndef _PLAYER_
#define _PLAYER_

//#include "Hand.h"
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"
#include "Deck.h"

class Strategy;

class Player {
public:
    Player ( Table& table, std::string strategy, Deck& deck);
    ~Player ();
    void printHand ();
    std::vector<Card> getPlayableCards();
    Command takeTurn ( std::vector<Card> playableCards);
    void playCard (Card c, std::vector<Card> playableCards);
    void removeCardInHand (Card c);
    void discardCard (Card c, std::vector<Card> playableCards);
    int getScore ();
    std::vector<Card> getDiscarded ();
    void clearPlayer();
    void assignHand (std::vector<Card> cards);
    void printTable ();
    void rageQuit ();
    void printDeck() {
        deck_->printDeck();
    }
protected:
    std::vector<Card> hand_;
    std::vector<Card> discarded_;
    Table* currentTable_;
    friend class StrategyHuman;
    friend class StrategyComputer;
    Strategy* currentStrategy_;
    Deck* deck_;
};

#endif
