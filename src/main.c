#include <raylib.h>
#include <stdio.h>

#include "game.h"
#include "sprite.h"
#include "update.h"
#include "render/render.h"


int main() {
	InitWindow(500, 500, "Hello World");
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
