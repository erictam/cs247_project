#include "Player.h"

class PlayerComputer : public Player {
public:
    PlayerComputer (std::vector <Card> cards) : Player(cards) {}
    void playCard () {}
};
