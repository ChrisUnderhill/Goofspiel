#include <stdio.h>
#include <vector>

using namespace std;


//Todo: give each player a unique randomly generated identifier upon connection
//such that if a player disconnects they can reconnect by supplying their UID.

class Player{
    //Player class will join up to the player's sockets somehow and take their
    //input. Player class may want to notify the game state that it has
    //selected.
    private:
        int ID;
        int numCards;
        vector<bool> hand;
        int currentSelection;

    public:
        vector<bool> getHand(){
            return hand;
        }

        int getID(){
            return ID;
        }

        // Play() will be called on all players simulatenously by the server
        // once everyone has selected a card
        int play(){
            if (currentSelection > 0){
                int temp = currentSelection;
                currentSelection = -1;
                return temp;
            }
            else{
                return -1
            }
        }

        bool hasPlayed(){
            return ( currentSelection > 0) ;
        }

        void selectCard(int card){
            currentSelection = card;
        }
};

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
        vector<bool> prizePile;
        vector<Player> players;
    public:
        bool checkRoundComplete(){
            for(std::vector<Player>::iterator it = players.begin(); it != players.end() ++it){
                if(  ! it->hasPlayed() ){
                    return false;
                }
            }
            return true;
        }

        void notify(int id);

        void runServer(int port)
        {
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
             while (1) {
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
                     exit(0);
                 id++;
                 }
                 else close(newsockfd);
             } /* end of while */
             close(sockfd);
             return 0; /* we never get here */
        }
};


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
        }else{
            //cout<<buffer[0];
            printf("Here is the message from sock %d : %s\n", id, buffer);
            n = write(sock,"I got your message",18);
            if (n < 0) error("ERROR writing to socket");
        }
    }
}
int main(){

}

