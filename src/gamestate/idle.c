#include "gamestate/idle.h"

#include "gamestate.h"
#include "gamestate/unit_selected.h"
#include "game.h"
#include "raylib.h"
#include "unit.h"
#include <stdbool.h>
#include <stdio.h>


static void end_turn() {
	// Note: Player 0 is not controlled, therefore we first mod, and then increase
	game.current_player %= game.player_count;
	game.current_player++;
	refresh_units();
}

static bool can_unit_be_selected(int unit) {
	return unit >= 0 && game.units[unit].owner == game.current_player &&
		!game.units[unit].moved;
}

void gamestate_idle_update() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		int unit = find_unit_at(game.cursor.x, game.cursor.y);
		if (can_unit_be_selected(unit))
			gamestate_unit_selected_enter(unit);
	}

	if (IsKeyReleased(KEY_Q))
		end_turn();
}

void gamestate_idle_enter() {
	game.gamestate.type = GAMESTATE_IDLE;
}
