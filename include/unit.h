#ifndef UNIT_H
#define UNIT_H

#include "vector.h"
#include <stdbool.h>


typedef enum {
    UNIT_TRUCK,
    UNIT_TRUCK_B,
    UNIT_APC,
    UNIT_TANK,
    UNIT_ARTILLERY,
    UNIT_BOMBER,
    UNIT_BCOPTER,
    UNIT_TCOPTER,
    UNIT_LANDER,
    UNIT_BATTLESHIP,
    UNIT_SUB,
    UNIT_INFANTRY,
    UNIT_MECH,
    UNIT_SIZE,
} UnitType;


typedef struct {
    UnitType unit_type;
    bool moved;
    short owner;
    short x;
    short y;
    short hp;
} Unit;


Unit unit_create(UnitType type, short owner, short x, short y);

VECTOR(UnitVec, Unit, unit_vec);

#endif // UNIT_H
