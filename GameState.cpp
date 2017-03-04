#ifndef GAMESTATE_CPP
#define GAMESTATE_CPP

#include "GameState.h"
#include "Player.h"
#include <vector>
#include <stdio.h>


GameState::GameState(int cards, int players)
    :numCards(cards)
    ,numPlayers(players)
{}

void GameState::addPlayer(Player* p){
    players.push_back(p);
}


bool GameState::checkRoundComplete(){
    bool b = true;

    for( auto & player : players ){
        b = player->hasPlayed();
    }
    return b;
}


void GameState::playerSelect(int id, int card){
    printf("id = %d   card = %d \n", id, card);
    players[id]->selectCard(card);
    printf("players card = %d\n", players[0]->getSelection());
    printf("players hasPlayed = %d\n", this->players[id]->hasPlayed());

}



#endif
