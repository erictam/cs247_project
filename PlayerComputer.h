#include "Player.h"

class PlayerComputer : public Player {
public:
    PlayerComputer ( Table& table);
    Command takeTurn (std::vector<Card> playableCards);
};
