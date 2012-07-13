#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"
#include "Deck.h"

class Strategy;

class Player {
public:
    Player ( Table& table, std::string strategy, Deck& deck);       //public constructor
    ~Player ();                                                     //public destructor
    std::vector<Card> getHand() const;
    std::vector<Card> getPlayableCards() const;                     //method to get a list of playable cards in the player's hand
    Command takeTurn ();                                            //method to get player to take his turn
    bool playCard( Card c);
    bool discardCard (Card c);
    void removeCardInHand (Card c);                                 //method to remove card from hand
    std::vector<Card> getDiscarded () const;                        //method to get list of discarded cards
    void clearPlayer();                                             //method to clear player's hand, discard pile
    void assignHand (std::vector<Card> cards);                      //method to assign new hand to player
    void rageQuit ();                                               //method to get player to ragequit
    
    bool getIsHuman() const;

private:
    std::vector<Card> hand_;
    std::vector<Card> discarded_;
    Table* currentTable_;
    Strategy* currentStrategy_;
    Deck* deck_;
    friend class StrategyComputer;

    bool isHuman_;
};

#endif
