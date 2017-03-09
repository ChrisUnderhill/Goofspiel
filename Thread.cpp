#ifndef THREAD_CPP
#define THREAD_CPP

#include <vector>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <pthread.h>
#include "Thread.h"
#include "GameState.h"


struct arg_struct{
    Thread* arg1;
    int arg2;
    int arg3;
    GameState* arg4;
};

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

static void* connectClient(void* arg);

void* Thread::runServer()
{
    int port = 5000;
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    pthread_t threads[10];

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

        arg_struct args = {this, newsockfd, id, gs};

        pthread_create(&threads[id], NULL, connectClient, &args);
        /*
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
            dostuff(newsockfd, id);
            exit(0);
        }
        */
        //close(newsockfd);
        id++;
    } /* end of while */
    close(sockfd);
}

Thread::Thread(GameState* game)
    :gs(game)
{
    printf("original game = %p     new game = %p\n", game, gs);
    numCards=game->getNumCards();
};

static void* runThread(void* arg);

int Thread::start()
{
    int result = pthread_create(&threadLoc, NULL, runThread, this);
    if (result == 0){
        running = 1;
    }
    return result;
}

static void* runThread(void* arg){
    return (((Thread*)arg)->runServer());
}

int Thread::join(){
    int result = -1;
    if (running == 1){
        result = pthread_join(threadLoc, NULL);
        if (result == 0){
            detached = 1;
        }
    }
    return result;
}

int Thread::detach(){
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
void* Thread::dostuff (GameState* gs, int sock, int id)
{
    Player player1(id, numCards);
    gs->addPlayer(&player1);
    printf("%p\n", &gs);
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
            //gs->remPlayer(id);
            close(sock);
        }else{
            //cout<<buffer[0];
            //printf("Here is the message from sock %d : %s\n", id, buffer);
            //printf("number = %d\n", atoi(buffer));
            gs->mu.lock();
            gs->playerSelect(id, atoi(buffer));
            gs->mu.unlock();
            n = write(sock,"I got your message",18);
            if (n < 0) error("ERROR writing to socket");
        }
    }
}

static void* connectClient(void* arg){
    struct arg_struct *args = (struct arg_struct*) arg;
    return (((Thread*)args->arg1)->dostuff(args->arg4, args->arg2, args->arg3));
}


#endif
