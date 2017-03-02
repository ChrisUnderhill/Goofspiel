#ifndef PLAYER_H
#define PLAYER_H


#include <vector>

class Player{
    //Player class will join up to the player's sockets somehow and take their
    //input. Player class may want to notify the game state that it has
    //selected.
    private:
        int ID;
        int numCards;
        std::vector<bool> hand;
        int currentSelection;

    public:
        Player(int id, int cards);
        std::vector<bool> getHand();
        int getID();
        int play();
        bool hasPlayed();
        void selectCard(int card);
};

#endif
