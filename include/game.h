#ifndef GAME_H
#define GAME_H

#include "gamestate.h"
#include "map.h"
#include "raylib.h"
#include "unit.h"

#define GAME_UNIT_MAX 32


typedef struct {
    Camera2D camera;
    Map map;
    GameState gamestate;
    Vector2 cursor;
    int player_count;
    int current_player;
    int unit_count;
    Unit units[GAME_UNIT_MAX];
} Game;


extern Game game;


void game_init();
void game_destroy();
void game_add_unit(Unit unit);

void refresh_units();
int find_unit_at(int x, int y);
bool is_occupied(int x, int y);

#endif // GAME_H
