#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <pthread.h>
#include "Player.h"

class GameState{
    //GameState stores basic info like the number of cards that the game is
    //being played with (can be more than 13 if we wish), number of players and
    //obviously the prize pool. The players are stored in a vector and each
    //player will notify the Gamestate when they have selected their card (so
    //that AIs can run in seperate threads). Once all players have notified we
    //retrieve their selection and play the round
    //Need to implement actually gameplay functions...
    //Prizes are vector<bool> for efficiency, each bit reperesent the nth value
    //card

    private:
        int numCards;
        int numPlayers;
        std::vector<bool> prizePile;
        std::vector<Player> players;
        pthread_t threadLoc;
        int threadCount = 0;

        int running;
        int detached;

    public:
        GameState(int cards, int players);
        bool checkRoundComplete();
        void notify(int id);
        void makeServer();

        void* runServer();
        int start();
        int join();
        int detach();
};

#endif



