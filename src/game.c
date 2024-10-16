#include "game.h"
#include "gamestate.h"
#include "map.h"
#include "map_debug.h"
#include "map_tiled.h"
#include "unit.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

Game game;

static void update_players();

void game_init() {
	game.camera.zoom = 2.0f;

	game.unit_count = 0;
	game.map = map_tiled_load("assets/sample_map.tmj");
	memset(&game.gamestate, 0, sizeof(GameState));
	game.gamestate.type = GAMESTATE_IDLE;

	game.cursor.x = 0;
	game.cursor.y = 0;
	
	game.players = 0b11110;
	game.current_player = 0;
	game.player_count = 4;

	update_players();
	end_turn();
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

static void update_players() {
	int new_players = 0;
	for (int i = 0; i < game.unit_count; i++)
		new_players = new_players | (1 << game.units[i].owner);
	if (game.players != new_players) {
		printf("New players: %b -> %b", game.players, new_players);
		game.players = new_players;
	}
}

void remove_unit(int unit) {
	assert(unit < game.unit_count && unit >= 0);
	game.units[unit] = game.units[--game.unit_count];
	update_players();
}


void end_turn() {
	// Note: Player 0 is not controlled, therefore we first mod, and then increase
	do {
		game.current_player %= game.player_count;
		game.current_player++;
	} while (!(game.players & (1 << game.current_player)));
	refresh_units();

	int winner = -1;
	int players_left = 0;
	for (int i = 1; i <= game.player_count; i++) {
		if (game.players & 1 << i) {
			players_left++;
			winner = i;
		}
	}
	if (players_left == 1) {
		gamestate_gameover_enter(winner);
	}
}
