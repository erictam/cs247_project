#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

// Card constructor, takes in a suit and rank enums
Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}

// Accessor - returns suit of card
Suit Card::getSuit() const{
	return suit_;
}

// Accessor - returns rank of card
Rank Card::getRank() const{
	return rank_;
}

// Returns true if the suit and rank are the same
bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

// Outputs card information
ostream &operator<<(ostream &out, const Card &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

// Reads in a card with the format <Suit><Rank>
istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
