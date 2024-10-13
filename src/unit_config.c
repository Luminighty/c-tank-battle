#include "unit_config.h"
#include "unit.h"


static const int speed_table[] = {
	[UNIT_INFANTRY] = 14,
	[UNIT_TANK] = 14,
	[UNIT_PLANE] = 12,
	[UNIT_BOAT] = 12,
	[UNIT_ARTILLERY] = 12,
};
int unit_get_speed(UnitType unit_type) { 
	return speed_table[unit_type];
}

static const int range_table[] = {
	[UNIT_INFANTRY] = 3,
	[UNIT_TANK] = 5,
	[UNIT_PLANE] = 3,
	[UNIT_BOAT] = 5,
	[UNIT_ARTILLERY] = 9,
};

static const int unit_tile_weight_table[][6] = {
	[UNIT_INFANTRY] = {
		[TILETYPE_ROAD] = 4,
		[TILETYPE_GRASS] = 4,
		[TILETYPE_FOREST] = 6,
		[TILETYPE_WATER] = 999,
		[TILETYPE_HILL] = 999,
		[TILETYPE_BLOCK] = 999,
	},
	[UNIT_TANK] = {
		[TILETYPE_ROAD] = 2,
		[TILETYPE_GRASS] = 4,
		[TILETYPE_FOREST] = 8,
		[TILETYPE_WATER] = 999,
		[TILETYPE_HILL] = 999,
		[TILETYPE_BLOCK] = 999,
	},
	[UNIT_BOAT] = {
		[TILETYPE_ROAD] = 999,
		[TILETYPE_GRASS] = 999,
		[TILETYPE_FOREST] = 999,
		[TILETYPE_WATER] = 2,
		[TILETYPE_HILL] = 999,
		[TILETYPE_BLOCK] = 999,
	},
	[UNIT_PLANE] = {
		[TILETYPE_ROAD] = 2,
		[TILETYPE_GRASS] = 2,
		[TILETYPE_FOREST] = 2,
		[TILETYPE_WATER] = 2,
		[TILETYPE_HILL] = 999,
		[TILETYPE_BLOCK] = 999,
	},
	[UNIT_ARTILLERY] = {
		[TILETYPE_ROAD] = 2,
		[TILETYPE_GRASS] = 6,
		[TILETYPE_FOREST] = 8,
		[TILETYPE_WATER] = 999,
		[TILETYPE_HILL] = 999,
		[TILETYPE_BLOCK] = 999,
	},
};
int unit_get_tile_weight(UnitType unit_type, TileType tile) {
	return unit_tile_weight_table[unit_type][tile];
}

