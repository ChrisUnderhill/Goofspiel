#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <vector>
#include "Player.h"
#include <stdio.h>

Player::Player(int id, int cards)
    :ID(id)
    ,numCards(cards)
    ,currentSelection(-1)
{
    for (int i = 1; i <= numCards; i++){
        hand.push_back(true);
    }
}

Player::~Player(){
    //delete &ID;
    //delete &numCards;
    //delete &hand;
    //delete &currentSelection;
}

std::vector<bool> Player::getHand(){
    return hand;
}

int Player::getID(){
    return ID;
}

// Play() will be called on all players simultaneously by the server
// once everyone has selected a card
int Player::play(){
    if (currentSelection > 0){
        int temp = currentSelection;
        currentSelection = -1;
        return temp;
    }
    else{
        return -2;
    }
}

bool Player::hasPlayed(){
    return ( currentSelection > 0) ;
}

void Player::selectCard(int card){
    this->currentSelection = card;
    //printf("player: address = %d    my card is %d\n", this, currentSelection);
}

int Player::getSelection() {
    //printf("player %d: my card is %d\n", this, currentSelection);
    return currentSelection;
}

#endif
