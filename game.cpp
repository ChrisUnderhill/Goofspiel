#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <pthread.h>
//#include <thread>
//#include <boost/thread.hpp>
#include "Player.cpp"
#include "Thread.cpp"
#include "GameState.cpp"


using namespace std;


//Todo: give each player a unique randomly generated identifier upon connection
//such that if a player disconnects they can reconnect by supplying their UID.


int main(){
    GameState game1 = GameState( 13, 2);
    Player player1 = Player(1, 13);
    Thread thread1 = Thread();

    //printf("Constructed\n");
    //game1.start();
    //printf("Started\n");
    //game1.notify(0);
    //game1.detach();
    //game1.join();
    printf("Hello World");

    //TODO: The thread doesn't seem to ever stop executing even after ! is
    //sent.
    //There is also wierd behaviour where when multiple clients connect it
    //prints started and notifying again. Find out why this happens and fix it.
    //
}
