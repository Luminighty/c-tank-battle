#include "gamestate.h"

#include "game.h"
#include "gamestate/gameover.h"
#include "gamestate/idle.h"
#include "gamestate/unit_attack.h"
#include "gamestate/unit_selected.h"
#include "gamestate/movement.h"
#include "pathfinder.h"


void gamestate_update() {
	#define CASE(state, fn) case state: {fn;} break;
	switch (game.gamestate.type) {
	CASE(GAMESTATE_IDLE, gamestate_idle_update())
	CASE(GAMESTATE_UNIT_SELECTED, gamestate_unit_selected_update())
	CASE(GAMESTATE_UNIT_MOVE, gamestate_unit_move_update())
	CASE(GAMESTATE_UNIT_ATTACK, gamestate_unit_attack_update())
	CASE(GAMESTATE_GAMEOVER, gamestate_gameover_update())
	}
	#undef CASE
}


void gamestate_destroy(GameState* state) {
	switch (state->type) {
	case GAMESTATE_UNIT_SELECTED:
		pathfinder_destroy(&game.gamestate.unit_selected.movement_result);
		break;
	case GAMESTATE_UNIT_MOVE:
		pathfinder_destroy(&game.gamestate.unit_move.movement_result);
		break;
	case GAMESTATE_UNIT_ATTACK:
		pathfinder_destroy(&game.gamestate.unit_attack.attack);
		break;
	default:
		break;
	}
}

