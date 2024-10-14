#include "gamestate/unit_selected.h"

#include "game.h"
#include "raylib.h"
#include "unit_config.h"
#include <stdio.h>


static void gamestate_unit_selected_leave() {
	pathfinder_destroy(&game.gamestate.unit_selected.movement_result);
}

typedef struct {
	UnitType unit;
	Map* map;
} MovementPathFinderContext;


static int movement_get_weight(int x, int y, void* _context) {
	if (is_occupied(x, y))
		return 999;
	MovementPathFinderContext* context = _context;
	return unit_get_tile_weight(context->unit, map_get_tile(context->map, x, y));
}


void gamestate_unit_selected_enter(int unit) {
	game.gamestate.type = GAMESTATE_UNIT_SELECTED;
	game.gamestate.unit_selected.unit = unit;
	int x = game.units[unit].x / 16;
	int y = game.units[unit].y / 16;
	UnitType type = game.units[unit].unit_type;

	printf("Select unit\n");
	fflush(stdout);

	MovementPathFinderContext context;
	context.unit = type;
	context.map = &game.map;
	game.gamestate.unit_selected.movement_result = pathfinder_run(x, y, unit_get_speed(type), movement_get_weight, &context);
}

void gamestate_unit_selected_update() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		GameStateUnitSelected* gamestate = &game.gamestate.unit_selected;
		PathFinderNode* node = pathfinder_find(&gamestate->movement_result, game.cursor.x, game.cursor.y);

		if (!node) {
			gamestate_unit_selected_leave();
			game.gamestate.type = GAMESTATE_IDLE;
			return;
		}

		int unit = game.gamestate.unit_selected.unit;
		game.gamestate.type = GAMESTATE_UNIT_MOVE;
		game.gamestate.unit_move.movement_result = game.gamestate.unit_selected.movement_result;
		game.gamestate.unit_move.target = node;
		game.gamestate.unit_move.target_x = game.units[unit].x;
		game.gamestate.unit_move.target_y = game.units[unit].y;
		return;
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
		gamestate_unit_selected_leave();
		game.gamestate.type = GAMESTATE_IDLE;
	}
}

