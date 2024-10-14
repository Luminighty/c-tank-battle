#include "update.h"
#include "game.h"
#include "gamestate.h"
#include "raylib.h"
#include <stdbool.h>


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
	gamestate_update();
}

