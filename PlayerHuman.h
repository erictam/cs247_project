#include <stdlib.h>
#include "Player.h"

class PlayerHuman : public Player {
public:    
    PlayerHuman (std::vector <Card> cards) : Player(cards) {}
    void playCard () {
        Command c;
        std::cin>>c;
        if (c.type == QUIT) {
            exit(1);
        }
        else if (c.type == DECK) {

            
        }
    }
};
