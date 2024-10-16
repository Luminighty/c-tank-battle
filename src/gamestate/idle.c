#include "gamestate/idle.h"

#include "gamestate.h"
#include "gamestate/gameover.h"
#include "gamestate/unit_selected.h"
#include "game.h"
#include "raylib.h"
#include "unit.h"
#include <stdbool.h>


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
	if (IsKeyReleased(KEY_W)) {
		for (int i = game.unit_count - 1; i >= 0; i--) {
			if (game.units[i].owner != game.current_player)
				remove_unit(i);
		}
	}
}

void gamestate_idle_enter() {
	game.gamestate.type = GAMESTATE_IDLE;
}
