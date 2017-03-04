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
    printf("actual game = %d\n", &game1);
    Player player1 = Player(1, 13);
    game1.addPlayer(&player1);
    //printf("players card = %d\n", players[id]->getSelection());

    printf("player1 = %d, gamestate.player[0] = %d\n", &player1, game1.players[0]);

    Thread thread1 = &game1;

    thread1.start();

    int test = -9;
    int test2 = 5;
    int test3 = 0;
    player1.selectCard(999);
    while (true){
        sleep(1);
        test = player1.getSelection();
        test2= game1.players[0]->getSelection();
        game1.players[0]->selectCard(888);
        test3= thread1.gs->players[0]->getSelection();
        printf("%d\n", test);
        printf("%d\n", test2);
        printf("%d\n", test3);
        printf("gamep: %d      statep: %d\n", &player1, game1.players[0]);
    }
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
    //prints started and notifying again. Find out why this happens and fix it.  //
}
