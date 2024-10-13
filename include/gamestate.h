#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "pathfinder.h"
typedef enum {
    GAMESTATE_IDLE,
    GAMESTATE_UNIT_SELECTED,
    GAMESTATE_UNIT_MOVE,
} GameStateType;


typedef struct {
    int unit;
    PathFinderResult movement_result;
} GameStateUnitSelected;


typedef struct {
    int unit;
    PathFinderResult movement_result;
    PathFinderNode* target;
    int target_x;
    int target_y;
} GameStateUnitMove;


typedef struct {
    GameStateType type;
    union {
        GameStateUnitSelected unit_selected;
        GameStateUnitMove unit_move;
    };
} GameState;


#endif // GAMESTATE_H
