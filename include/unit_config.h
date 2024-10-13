#ifndef UNIT_CONFIG_H
#define UNIT_CONFIG_H


#include "map.h"
#include "unit.h"

int unit_get_speed(UnitType unit_type);
int unit_get_range(UnitType unit_type);
int unit_get_tile_weight(UnitType unit_type, TileType tile);


#endif // UNIT_CONFIG_H
