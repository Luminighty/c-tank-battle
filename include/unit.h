#ifndef UNIT_H
#define UNIT_H


#include <stdbool.h>
typedef enum {
    UNIT_INFANTRY,
    UNIT_TANK,
    UNIT_PLANE,
    UNIT_BOAT,
    UNIT_ARTILLERY,
    UNIT_SIZE,
} UnitType;


typedef struct {
    UnitType unit_type;
    bool moved;
    int owner;
    int x;
    int y;
    int hp;
} Unit;


Unit unit_create(UnitType type, int owner, int x, int y);
Unit unit_infantry(int owner, int x, int y);
Unit unit_tank(int owner, int x, int y);
Unit unit_plane(int owner, int x, int y);
Unit unit_boat(int owner, int x, int y);


#endif // UNIT_H
