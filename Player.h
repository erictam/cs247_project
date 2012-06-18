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
    void printHand ();                                              //method to print the hand of the player
    std::vector<Card> getPlayableCards();                           //method to get a list of playable cards in the player's hand
    Command takeTurn ();                                            //method to get player to take his turn
    void playCard (Card c, std::vector<Card>& playableCards);       //method to get player to play a card onto table
    void discardCard (Card c, std::vector<Card>& playableCards);    //method to get player to discard card into discard pile
    void removeCardInHand (Card c);                                 //method to remove card from hand
    int getScore ();                                                //method to get score calculated based on discard pile
    std::vector<Card> getDiscarded ();                              //method to get list of discarded cards
    void clearPlayer();                                             //method to clear player's hand, discard pile
    void assignHand (std::vector<Card> cards);                      //method to assign new hand to player
    void printTable ();                                             //method to print cards currently on table
    void rageQuit ();                                               //method to get player to ragequit
    void printDeck();                                               //method to print the deck (only needed to deck command) 
private:
    std::vector<Card> hand_;
    std::vector<Card> discarded_;
    Table* currentTable_;
    Strategy* currentStrategy_;
    Deck* deck_;
};

#endif
