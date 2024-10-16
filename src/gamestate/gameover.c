#include "gamestate/gameover.h"
#include "game.h"
#include "gamestate.h"


void gamestate_gameover_enter(int winner) {
	game.gamestate.type = GAMESTATE_GAMEOVER;
	game.gamestate.gameover.winner = winner;
}


void gamestate_gameover_update() {

}

