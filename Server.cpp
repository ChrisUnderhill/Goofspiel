#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <iostream>
#include <pthread.h>

fd_set readset, tempset;
int maxfd, flags;
int srvsock, peersock, j, result, result1, sent, len;
timeval tv;
char buffer[256+1];
sockaddr_in addr;


/* Here should go the code to create the server socket bind it to a port and call listen
    srvsock = socket(...);
    bind(srvsock ...);
    listen(srvsock ...);
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void* runServer()
{
    int port = 5000;
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(sockfd,5);
}


//FD_ZERO(&readset);
//FD_SET(srvsock, &readset);
//maxfd = srvsock;

void dothingy(){

do{
   memcpy(&tempset, &readset, sizeof(tempset));
   tv.tv_sec = 30;
   tv.tv_usec = 0;
   result = select(maxfd + 1, &tempset, NULL, NULL, &tv);

   if (result == 0) {
      printf("select() timed out!\n");
   }
   else if (result < 0 && errno != EINTR) {
      printf("Error in select(): %s\n", strerror(errno));
   }
   else if (result > 0) {

      if (FD_ISSET(srvsock, &tempset)) {
         len = sizeof(addr);
         peersock = accept(srvsock, &addr, &len);
         if (peersock < 0) {
            printf("Error in accept(): %s\n", strerror(errno));
         }
         else {
            FD_SET(peersock, &readset);
            maxfd = (maxfd < peersock)?peersock:maxfd;
         }
         FD_CLR(srvsock, &tempsock);
      }

      for (j=0; j<maxfd+1; j++) {
         if (FD_ISSET(j, &tempset)) {

            do {
               result = recv(j, buffer, MAX_BUFFER_SIZE, 0);
            } while (result == -1 && errno == EINTR);

            if (result > 0) {
               buffer[result] = 0;
               printf("Echoing: %s\n", buffer);
               sent = 0;

               do {
                  result1 = send(j, buffer+sent, result-sent, MSG_NOSIGNAL);
                  if (result1 > 0)
                     sent += result1;
                  else if (result1 < 0 && errno != EINTR);
                     break;
                } while (result > sent);

            }
            else if (result == 0) {
               close(j);
               FD_CLR(j, &readset);
            }
            else {
               printf("Error in recv(): %s\n", strerror(errno));
            }
         }      // end if (FD_ISSET(j, &tempset))
      }      // end for (j=0;...)
   }      // end else if (result > 0)
} while (1);

}
