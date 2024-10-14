#ifndef GAMESTATE_MOVEMENT_H
#define GAMESTATE_MOVEMENT_H

#include "pathfinder.h"


typedef struct {
    int unit;
    PathFinderResult movement_result;
    PathFinderNode* target;
    int target_x;
    int target_y;
} GameStateUnitMove;


void gamestate_unit_move_update();


#endif // GAMESTATE_MOVEMENT_H
