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
#include "Player.h"
#include "GameState.h"


using namespace std;


//Todo: give each player a unique randomly generated identifier upon connection
//such that if a player disconnects they can reconnect by supplying their UID.

void dostuff(int, int);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


//Player functions
vector<bool> Player::getHand(){
    return hand;
}

int Player::getID(){
    return ID;
}

// Play() will be called on all players simulatenously by the server
// once everyone has selected a card
int Player::play(){
    if (currentSelection > 0){
        int temp = currentSelection;
        currentSelection = -1;
        return temp;
    }
    else{
        return -1;
    }
}

bool Player::hasPlayed(){
    return ( currentSelection > 0) ;
}

void Player::selectCard(int card){
    currentSelection = card;
}


void* GameState::runServer()
{
    int port = 5000;
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    int id = 0;
    while (true) {
        newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
            //todo: ensure we run dostuff in a seperate thread otherwise we'll just crash
            dostuff(newsockfd, id);
            //printf("Reached after call to dostuff");
            exit(0);
            //close(newsockfd);

        }
        else close(newsockfd);
        id++;
    } /* end of while */
    close(sockfd);
}

GameState::GameState(int cards, int players){
    numCards=cards;
    numPlayers=players;
    prizePile = vector<bool>(cards, true);
}

bool GameState::checkRoundComplete(){
    for(std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it){
        if(  ! it->hasPlayed() ){
            return false;
        }
    }
    return true;

}

void GameState::notify(int id){
    //TODO: make it do stuff
    printf("YAY I HAVE NOTIFIED GO ME");
}

static void* runThread(void* arg);

int GameState::start()
{
    int result = pthread_create(&threadLoc, NULL, runThread, this);
    if (result == 0){
        running = 1;
    }
    return result;
}

static void* runThread(void* arg){
    return (((GameState*)arg)->runServer());
}

int GameState::join(){
    int result = -1;
    if (running == 1){
        result = pthread_join(threadLoc, NULL);
        if (result == 0){
            detached = 1;
        }
    }
    return result;
}

int GameState::detach(){
    int result = -1;
    if (running == 1 && detached == 0){
        result = pthread_detach(threadLoc);
        if (result == 0){
            detached = 1;
        }
    }
    return result;
}


/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff (int sock, int id)
{
    int n;
    char buffer[256]; 

    bool active = true;
    while (active){
        bzero(buffer,256);
        n = read(sock,buffer,256);
        if (n < 0) error("ERROR reading from socket");
        if (buffer[0] == '!') {
            printf("Breaking upon receiveing !");
            n = write(sock, "!", 1);
            active = false;
            //close(sock);
            return;
        }else{
            //cout<<buffer[0];
            printf("Here is the message from sock %d : %s\n", id, buffer);
            n = write(sock,"I got your message",18);
            if (n < 0) error("ERROR writing to socket");
        }
    }
}

int main(){
    GameState game1 = GameState( 13, 2);
    printf("Constructed\n");
    game1.start();
    printf("Started\n");
    //game1.notify(0);
    //game1.detach();
    game1.join();

    printf("Joined");
    return 0;
    //TODO: The thread doesn't seem to ever stop executing even after ! is
    //sent.
    //There is also wierd behaviour where when multiple clients connect it
    //prints started and notifying again. Find out why this happens and fix it.
    //
}

