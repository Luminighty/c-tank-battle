#include "game.h"
#include "gamestate.h"
#include "map.h"
#include "map_debug.h"
#include "pathfinder.h"
#include "unit.h"
#include <stdio.h>

Game game;

void game_init() {
	game.camera.zoom = 2.0f;

	game_add_unit(unit_tank(1, 16, 16));
	game_add_unit(unit_infantry(2, 32, 32));
	game_add_unit(unit_plane(3, 64, 32));
	game_add_unit(unit_boat(4, 64, 64));

	game.map = map_debug_create();
}

void game_destroy() {
	map_destroy(&game.map);
	switch (game.gamestate.type) {
	case GAMESTATE_UNIT_SELECTED:
		pathfinder_destroy(&game.gamestate.unit_selected.movement_result);
		break;
	default:
		break;
	}
}

void game_add_unit(Unit unit) {
	if (game.unit_count >= GAME_UNIT_MAX) {
		printf("Could not create new unit. Unitcap reached!");
		return;
	}
	game.units[game.unit_count] = unit;
	game.unit_count++;
}

