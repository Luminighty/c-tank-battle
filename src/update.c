#include "update.h"
#include "game.h"
#include "gamestate.h"
#include "map.h"
#include "pathfinder.h"
#include "raylib.h"
#include "unit.h"
#include "unit_config.h"
#include <stdbool.h>
#include <stdio.h>


static int find_unit_at(int x, int y) {
	// When finding units, we don't expect them to be in sub tiles
	x *= 16;
	y *= 16;
	for (int i = 0; i < game.unit_count; i++)
		if (game.units[i].x == x && game.units[i].y == y)
			return i;
	return -1;
}

static bool is_occupied(int x, int y) {
	return find_unit_at(x, y) >= 0;
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

static void on_unit_selected(int unit) {
	printf("Select unit %d\n", unit);
	game.gamestate.type = GAMESTATE_UNIT_SELECTED;
	game.gamestate.unit_selected.unit = unit;
	int x = game.units[unit].x / 16;
	int y = game.units[unit].y / 16;
	UnitType type = game.units[unit].unit_type;
	unit_get_speed(type);

	MovementPathFinderContext context;
	context.unit = type;
	context.map = &game.map;
	game.gamestate.unit_selected.movement_result = pathfinder_run(x, y, unit_get_speed(type), movement_get_weight, &context);
}

static void gamestate_idle() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		int unit = find_unit_at(game.cursor.x, game.cursor.y);
		if (unit >= 0)
			on_unit_selected(unit);
	}
}

static void gamestate_unit_selected_leave() {
	pathfinder_destroy(&game.gamestate.unit_selected.movement_result);
}

static void gamestate_unit_selected() {
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

static inline int sign(int v) {
	if (v == 0)
		return 0;
	return v > 0 ? 1 : -1;
}

static void gamestate_unit_move_leave() {
	pathfinder_destroy(&game.gamestate.unit_move.movement_result);
}

static void gamestate_unit_move() {
	GameStateUnitMove* gamestate = &game.gamestate.unit_move;
	Unit* unit = &game.units[gamestate->unit];
	if (unit->x == gamestate->target_x && unit->y == gamestate->target_y) {
		// Find next target
		PathFinderNode* new_target = gamestate->target;
		
		if (gamestate->target->x * 16 == gamestate->target_x && gamestate->target->y * 16 == gamestate->target_y) {
			gamestate_unit_move_leave();
			game.gamestate.type = GAMESTATE_IDLE;
			printf("Reached target\n");
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

static inline void update_cursor() {
	Vector2 position = GetMousePosition();
	position = GetScreenToWorld2D(position, game.camera);
	int tile_x = position.x / 16;
	int tile_y = position.y / 16;
	game.cursor.x = tile_x;
	game.cursor.y = tile_y;
}

void update() {
	update_cursor();
	switch (game.gamestate.type) {
	case GAMESTATE_IDLE:
		gamestate_idle();
		break;
	case GAMESTATE_UNIT_SELECTED:
		gamestate_unit_selected();
		break;
	case GAMESTATE_UNIT_MOVE:
		gamestate_unit_move();
		break;
	}

}
