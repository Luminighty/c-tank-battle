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

static void draw_outlined_text(const char* text, int pos_x, int pos_y, int font_size, Color color, int outline_size, Color outline_color) {
	DrawText(text, pos_x - outline_size, pos_y - outline_size, font_size, outline_color);
	DrawText(text, pos_x + outline_size, pos_y - outline_size, font_size, outline_color);
	DrawText(text, pos_x - outline_size, pos_y + outline_size, font_size, outline_color);
	DrawText(text, pos_x + outline_size, pos_y + outline_size, font_size, outline_color);
	DrawText(text, pos_x, pos_y, font_size, color);
}

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

#define FN_CASE(value, fn) case value: {fn;} break;

static void render_gamestate() {
	switch (game.gamestate.type) {
		FN_CASE(GAMESTATE_UNIT_SELECTED, render_unit_selected())
		FN_CASE(GAMESTATE_UNIT_ATTACK, render_unit_attack())
		default:
			render_units();
			break;
	}
}

static const Rectangle UNIT_MAP[] = {
	[UNIT_INFANTRY] = UNIT(11),
	[UNIT_TANK] = UNIT(3),
	[UNIT_BOAT] = UNIT(8),
	[UNIT_PLANE] = UNIT(5),
};
