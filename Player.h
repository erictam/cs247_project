#ifndef _PLAYER_
#define _PLAYER_

//#include "Hand.h"
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Strategy;

class Player {
public:
    Player ( Table& table, std::string strategy);
    ~Player ();
    void printHand ();
    std::vector<Card> getPlayableCards();
    Command takeTurn ( std::vector<Card> playableCards);
    bool playCard (Card c, std::vector<Card> playableCards);
    void removeCardInHand (Card c);
    bool discardCard (Card c, std::vector<Card> playableCards);
    int getScore ();
    std::vector<Card> getDiscarded ();
    void clearPlayer();
    void assignHand (std::vector<Card> cards);
    void printTable ();
    void rageQuit ();
protected:
    std::vector<Card> hand_;
    std::vector<Card> discarded_;
    Table* currentTable_;
    friend class StrategyHuman;
    friend class StrategyComputer;
    Strategy* currentStrategy_;
};

#endif
