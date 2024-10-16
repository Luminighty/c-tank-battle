#include <raylib.h>
#include <stdio.h>

#include "game.h"
#include "sprite.h"
#include "update.h"
#include "render/render.h"


int main() {
	InitWindow(16*30*2, 16*17*2, "Tank Battle");
	SetTargetFPS(60);

	texture_tilemap = LoadTexture("assets/tilemap.png");

	game_init();
	while(!WindowShouldClose()) {
		update();
		render();
		fflush(stdout);
	}
	game_destroy();

	UnloadTexture(texture_tilemap);
	CloseWindow();
	return 0;
}
