#include "game.h"
#include "gamestate.h"
#include "map.h"
#include "map_debug.h"
#include "unit.h"
#include <stdio.h>
#include <string.h>

Game game;

void game_init() {
	game.camera.zoom = 2.0f;

	game.map = map_debug_create();
	memset(&game.gamestate, 0, sizeof(GameState));
	game.gamestate.type = GAMESTATE_IDLE;

	game.cursor.x = 0;
	game.cursor.y = 0;
	
	game.current_player = 1;
	game.player_count = 4;

	game.unit_count = 0;
	game_add_unit(unit_tank(1, 16, 16));
	game_add_unit(unit_infantry(2, 32, 32));
	game_add_unit(unit_plane(3, 64, 32));
	game_add_unit(unit_boat(4, 64, 64));
}

void game_destroy() {
	map_destroy(&game.map);
	gamestate_destroy(&game.gamestate);
}

void game_add_unit(Unit unit) {
	if (game.unit_count >= GAME_UNIT_MAX) {
		printf("Could not create new unit. Unitcap reached!");
		return;
	}
	game.units[game.unit_count] = unit;
	game.unit_count++;
}


int find_unit_at(int x, int y) {
	// When finding units, we don't expect them to be in sub tiles
	x *= 16;
	y *= 16;
	for (int i = 0; i < game.unit_count; i++)
		if (game.units[i].x == x && game.units[i].y == y)
			return i;
	return -1;
}


bool is_occupied(int x, int y) {
	return find_unit_at(x, y) >= 0;
}

void refresh_units() {
	for (int i = 0; i < game.unit_count; i++)
		game.units[i].moved = false;
}
