#ifndef GAMESTATE_CPP
#define GAMESTATE_CPP

#include "GameState.h"
#include "Player.h"
#include <vector>


GameState::GameState(int cards, int players)
    :numCards(cards)
    ,numPlayers(players)
{};


bool GameState::checkRoundComplete(){
    bool b = true;

    for( auto & player : players ){
        b = player.hasPlayed();
    }
    return b;
}


#endif
