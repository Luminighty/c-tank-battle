#ifndef GAME_H
#define GAME_H

#include "gamestate.h"
#include "map.h"
#include "raylib.h"
#include "unit.h"

#define GAME_UNIT_MAX 32


typedef struct {
    Camera2D camera;
    Vector2 cursor;
    int players;
    int player_count;
    int current_player;
    int unit_count;
    Unit units[GAME_UNIT_MAX];
    UnitVec units_2;
    Map map;
    GameState gamestate;
} Game;


extern Game game;

void test() {
    game.units_2 = unit_vec_create();
    unit_vec_add(&game.units_2, unit_create(UNIT_INFANTRY, 1, 16, 16));
}


void game_init();
void game_destroy();
void game_add_unit(Unit unit);

void refresh_units();
int find_unit_at(int x, int y);
bool is_occupied(int x, int y);
void remove_unit(int unit);
void end_turn();

#endif // GAME_H
