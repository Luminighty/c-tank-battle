#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gamestate/gameover.h"
#include "gamestate/movement.h"
#include "gamestate/unit_attack.h"
#include "gamestate/unit_selected.h"


typedef enum {
    GAMESTATE_IDLE,
    GAMESTATE_GAMEOVER,
    GAMESTATE_UNIT_SELECTED,
    GAMESTATE_UNIT_ATTACK,
    GAMESTATE_UNIT_MOVE,
} GameStateType;


typedef struct {
    GameStateType type;
    union {
        GameStateUnitSelected unit_selected;
        GameStateUnitMove unit_move;
        GameStateUnitAttack unit_attack;
        GameStateGameOver gameover;
    };
} GameState;


void gamestate_update();
void gamestate_destroy(GameState* state);

#endif // GAMESTATE_H
