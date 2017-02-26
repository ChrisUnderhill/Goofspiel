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
    //GameState sotres basic info like the number of cards that the game is
    //being played with (can be more than 13 if we wish), number of players and
    //obviously the prize pool. The players are stored in a vector and each
    //player will notify the Gamestate when they have selected their card (so
    //that AIs can run in seperate threads). Once all players have notified we
    //retrieve their selection and play the round
    //Need to implement actually gameplay functions...
    //
    //Prizes are vector<bool> for efficiency, each bit reperesent the nth value
    //card
    private:
        int numCards;
        int numPlayers;
        vector<bool> prizePile;
        vector<Player> players;

    public:
        void notify(int id){}
};

int main(){

}

