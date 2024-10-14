#ifndef GAMESTATE_UNIT_SELECTED_H
#define GAMESTATE_UNIT_SELECTED_H

#include "pathfinder.h"


typedef struct {
    int unit;
    PathFinderResult movement_result;
} GameStateUnitSelected;


void gamestate_unit_selected_enter(int unit);
void gamestate_unit_selected_update();


#endif // GAMESTATE_UNIT_SELECTED_H
