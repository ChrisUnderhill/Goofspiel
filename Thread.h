#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "GameState.h"

class Thread{
    //Thread stores basic info like the number of cards that the game is
    //being played with (can be more than 13 if we wish), number of players and
    //obviously the prize pool. The players are stored in a vector and each
    //player will notify the Gamestate when they have selected their card (so
    //that AIs can run in seperate threads). Once all players have notified we
    //retrieve their selection and play the round
    //Need to implement actually gameplay functions...
    //Prizes are vector<bool> for efficiency, each bit reperesent the nth value
    //card

    private:
        pthread_t threadLoc;
        int threadCount = 0;
        int running;
        int detached;
        int numCards;

    public:
        Thread(GameState* game);
        void makeServer();
        void* dostuff(GameState* gs, int sock, int id);

        void* runServer();
        int start();
        int join();
        int detach();
        GameState* gs;
};

#endif



