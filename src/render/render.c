#include "render/render.h"
#include "game.h"
#include "gamestate.h"
#include "pathfinder.h"
#include "raylib.h"
#include "render/render_map.h"
#include "sprite.h"
#include "unit.h"
#include "unit_config.h"
#include <stdio.h>


static const Rectangle UNIT_MAP[];

static void render_gamestate();


static const Color player_color[] = {
	GRAY,
	DARKGREEN,
	BLUE,
	{ 0xA3, 0, 0, 255 },
	{ 230, 130, 0, 255 }
};

static const Color player_bright_color[] = {
	GRAY,
	GREEN,
	SKYBLUE,
	{ 255, 100, 100, 255 },
	{ 255, 200, 150, 255 }
};

static void render_units() {
	for (int i = 0; i < game.unit_count; i++) {
		Unit* unit = &game.units[i];
		Rectangle source = UNIT_MAP[unit->unit_type];
		source.y += unit->owner * 16;
		Vector2 position = { unit->x, unit->y };
		Color color = unit->moved ? GRAY : WHITE;
		DrawTextureRec(texture_tilemap, source, position, color);
 
		int max_hp = unit_get_hp(unit->unit_type); 
		int hp = unit->hp * 10;
		int hp_number = hp / max_hp;
		if (hp_number <= 9 && hp_number >= 0) {
			DrawTextureRec(texture_tilemap, SPRITE(hp_number, 10), position, WHITE);
		}
	}
}

void render() {
	BeginDrawing();
	BeginMode2D(game.camera);
	ClearBackground(RAYWHITE);

	render_map(&game.map);

	render_gamestate();

	Vector2 cursor_position = { game.cursor.x * 16, game.cursor.y * 16 };
	DrawTextureRec(texture_tilemap, SPRITE(7, 3), cursor_position, WHITE);

	EndMode2D();

	// Draw UI
	DrawText(TextFormat("PLAYER %01i", game.current_player), 10, 10, 20, player_color[game.current_player]);

	if (game.gamestate.type == GAMESTATE_GAMEOVER) {
		int winner = game.gamestate.gameover.winner;
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 150});
		DrawText(TextFormat("GAME OVER\nPLAYER %01i WINS", winner), 8*16, 8*16, 40, player_bright_color[winner]);
	}

	EndDrawing();
}

static void render_unit_selected() {
	PathFinderResult* result = &game.gamestate.unit_selected.movement_result;
	for (int i = 0; i < result->node_count; i++) {
		Vector2 position = { result->nodes[i].x * 16, result->nodes[i].y * 16 };
		DrawTextureRec(texture_tilemap, SPRITE(7, 4), position, (Color){255, 255, 255, 200});
	}
	render_units();
}

static void render_unit_attack() {
	PathFinderResult* result = &game.gamestate.unit_attack.attack;
	for (int i = 0; i < result->node_count; i++) {
		Vector2 position = { result->nodes[i].x * 16, result->nodes[i].y * 16 };
		DrawTextureRec(texture_tilemap, SPRITE(7, 4), position, (Color){200, 0, 0, 125});
	}
	render_units();

	for (int i = 0; i < result->node_count; i++) {
		int x = result->nodes[i].x;
		int y = result->nodes[i].y;

		int unit = find_unit_at(x, y);
		if (unit >= 0 && game.units[unit].owner != game.current_player) {
			Vector2 position = { result->nodes[i].x * 16, result->nodes[i].y * 16 };
			DrawTextureRec(texture_tilemap, SPRITE(7, 3), position, RED);
		}
	}
}


static void render_gamestate() {
	#define CASE(value, fn) case value: {fn;} break;
	switch (game.gamestate.type) {
		CASE(GAMESTATE_UNIT_SELECTED, render_unit_selected())
		CASE(GAMESTATE_UNIT_ATTACK, render_unit_attack())
		default:
			render_units();
			break;
	}
	#undef CASE
}

static const Rectangle UNIT_MAP[] = {
	[UNIT_INFANTRY] = UNIT(11),
	[UNIT_TANK] = UNIT(3),
	[UNIT_BOAT] = UNIT(8),
	[UNIT_PLANE] = UNIT(5),
};
