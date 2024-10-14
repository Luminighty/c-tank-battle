#include "gamestate.h"

#include "game.h"
#include "gamestate/idle.h"
#include "gamestate/unit_attack.h"
#include "gamestate/unit_selected.h"
#include "gamestate/movement.h"
#include "pathfinder.h"


void gamestate_update() {
	switch (game.gamestate.type) {
	case GAMESTATE_IDLE:
		gamestate_idle_update();
		break;
	case GAMESTATE_UNIT_SELECTED:
		gamestate_unit_selected_update();
		break;
	case GAMESTATE_UNIT_MOVE:
		gamestate_unit_move_update();
		break;
	case GAMESTATE_UNIT_ATTACK:
		gamestate_unit_attack_update();
		break;
	}
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

