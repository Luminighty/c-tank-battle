#include "gamestate/unit_attack.h"
#include "game.h"
#include "gamestate.h"
#include "gamestate/idle.h"
#include "pathfinder.h"
#include "raylib.h"
#include "unit_config.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	UnitType unit;
	Map* map;
} AttackPathFinderContext;

static void gamestate_unit_attack_leave() {
	game.units[game.gamestate.unit_attack.unit].moved = true;
	pathfinder_destroy(&game.gamestate.unit_attack.attack);
	gamestate_idle_enter();
}

static int attack_get_weight(int x, int y, void* _context) {
	if (is_occupied(x, y))
		return 1;
	AttackPathFinderContext* context = _context;
	return 1;
}


void gamestate_unit_attack_enter(int unit) {
	game.gamestate.type = GAMESTATE_UNIT_ATTACK;
	GameStateUnitAttack* gamestate = &game.gamestate.unit_attack;
	gamestate->unit = unit;
	int x = game.units[unit].x / 16;
	int y = game.units[unit].y / 16;
	UnitType type = game.units[unit].unit_type;
	AttackPathFinderContext context;
	context.unit = type;
	context.map = &game.map;

	gamestate->attack = pathfinder_run(x, y, unit_get_range(type), attack_get_weight, &context);

	bool found_unit = false;
	for (int i = 0; i < gamestate->attack.node_count; i++) {
		PathFinderNode* node = &gamestate->attack.nodes[i];
		int unit = find_unit_at(node->x, node->y);
		if (unit >= 0 && game.units[unit].owner != game.current_player) {
			found_unit = true;
			break;
		}
	}

	if (!found_unit) {
		gamestate_unit_attack_leave();
	}
}


void gamestate_unit_attack_update() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		GameStateUnitAttack* gamestate = &game.gamestate.unit_attack;
		PathFinderNode* node = pathfinder_find(&gamestate->attack, game.cursor.x, game.cursor.y);

		if (!node) {
			gamestate_unit_attack_leave();
			return;
		}

		int targeted_unit = find_unit_at(game.cursor.x, game.cursor.y);
		if (targeted_unit < 0)
			return;

		if (game.units[targeted_unit].owner == game.current_player)
			return;

		printf("Attacking %d\n", targeted_unit);
		fflush(stdout);
		game.units[targeted_unit].hp -= unit_get_power(game.units[gamestate->unit].unit_type);
		// Do fancy stuff
		gamestate_unit_attack_leave();
	}
}

