#include "gamestate/movement.h"
#include "game.h"
#include "gamestate/unit_attack.h"
#include "math.h"
#include "unit.h"
#include <stdio.h>


static void gamestate_unit_move_leave() {
	pathfinder_destroy(&game.gamestate.unit_move.movement_result);
}


void gamestate_unit_move_update() {
	GameStateUnitMove* gamestate = &game.gamestate.unit_move;
	int unit_index = gamestate->unit;
	Unit* unit = &game.units[unit_index];
	if (unit->x == gamestate->target_x && unit->y == gamestate->target_y) {
		// Find next target
		PathFinderNode* new_target = gamestate->target;
		
		if (gamestate->target->x * 16 == gamestate->target_x && gamestate->target->y * 16 == gamestate->target_y) {
			gamestate_unit_move_leave();
			gamestate_unit_attack_enter(unit_index);
			return;
		}

		while (new_target) {
			PathFinderNode* prev = pathfinder_prev(&gamestate->movement_result, new_target);
			if (prev->x * 16 == gamestate->target_x && prev->y * 16 == gamestate->target_y)
				break;
			new_target = prev;
		}

		if (!new_target) {
			printf("New target not found while moving!!!\n");
			printf("Original Target: ");
			pathfinder_node_print(gamestate->target);
			printf("\n");
			pathfinder_print(&gamestate->movement_result);
		}

		gamestate->target_x = new_target->x * 16;
		gamestate->target_y = new_target->y * 16;
	}
	int dx = sign(gamestate->target_x - unit->x) * 2;
	int dy = sign(gamestate->target_y - unit->y) * 2;
	unit->x += dx;
	unit->y += dy;
}

