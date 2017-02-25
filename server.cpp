#include <stdio.h>
#include <vector>

using namespace std;

class Player{
    //Player class will join up to the player's sockets somehow and take their
    //input. Bool played needs resetting at the start of each round and stores
    //not quite sure what's going on with play() and selectCard, we probably
    //only need one.
    private:
        int ID;
        int numCards;
        vector<bool> hand;
        int currentSelection;
        bool played;

    public:
        vector<bool> getHand(){
            return hand;
        }

        int getID(){
            return ID;
        }

        int play(){
            played = false;
            return currentSelection;
        }

        bool hasPlayed(){
            return played;
        }

        void selectCard(int card){
            currentSelection = card;
            played = true;

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

