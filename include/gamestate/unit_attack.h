#ifndef GAMESTATE_UNIT_ATTACK_H
#define GAMESTATE_UNIT_ATTACK_H


#include "pathfinder.h"


typedef struct {
    int unit;
    PathFinderResult attack;
} GameStateUnitAttack;


void gamestate_unit_attack_enter(int unit);
void gamestate_unit_attack_update();


#endif // GAMESTATE_UNIT_ATTACK_H
