#include "map_tiled.h"
#include "game.h"
#include "libs/json.h"
#include "map.h"
#include "unit.h"
#include <stdio.h>
#include <string.h>


#define TILED_GUID unsigned int

static Tile find_tile(TILED_GUID index);
static MapObject find_object(TILED_GUID index);
static void load_unit(Map* map, int x, int y, TILED_GUID id);

static TILED_GUID TILE_MAP[];
static TILED_GUID MAPOBJECT_MAP[];


static const TILED_GUID TILED_FLIP_H =  0x80000000;
static const TILED_GUID TILED_FLIP_V =  0x40000000;
static const TILED_GUID TILED_FLIP_D =  0x20000000;
static const TILED_GUID TILED_ROTATED = 0x10000000;
static const TILED_GUID TILED_GUID_PART = ~(TILED_FLIP_H | TILED_FLIP_V | TILED_FLIP_D | TILED_ROTATED);

Map map_tiled_load(const char *filename) {
	JsonValue* map_data = json_loadf(filename);


	int height = json_as_number(json_object_get(map_data, "height"));
	int width = json_as_number(json_object_get(map_data, "width"));
	
	Map map = map_create(width, height);

	JsonValue* layers = json_object_get(map_data, "layers");
	int layer_count = json_array_length(layers);
	for (int i = 0; i < layer_count; i++) {
		JsonValue* layer = json_array_get(layers, i);

		JsonValue* data = json_object_get(layer, "data");
		int data_length = json_array_length(data);

		for (int j = 0; j < data_length; j++) {
			int x = j % width;
			int y = j / width;
			TILED_GUID id = json_as_number(json_array_get(data, j));
			id = id & TILED_GUID_PART;

			Tile tile = find_tile(id);
			if (tile != TILE_NONE)
				map_set_tile(&map, x, y, tile);
			MapObject map_object = find_object(id);
			if (map_object != MAPOBJECT_NONE)
				map_set_object(&map, x, y, map_object);

			load_unit(&map, x, y, id);
		}
	}

	json_destroy(map_data);
	return map;
}


static Tile find_tile(TILED_GUID id) {
	for (int i = 0; i < TILE_SIZE; i++)
		if (TILE_MAP[i] == id)
			return i;
	return TILE_NONE;
}


static MapObject find_object(TILED_GUID id) {
	for (int i = 0; i < MAPOBJECT_SIZE; i++)
		if (MAPOBJECT_MAP[i] == id)
			return i;
	return MAPOBJECT_NONE;
}


static void load_unit(Map* map, int x, int y, TILED_GUID id) {
	if (id == 0)
		return;
	id--;
	TILED_GUID id_x = id % 18;
	TILED_GUID id_y = id / 18;
	if (id_x < 5 || id_y < 5 || id_y > 9)
		return;
	int owner = id_y - 5;
	TILED_GUID unit_type = id_x - 5;
	game_add_unit(unit_create(unit_type, owner, x * 16, y * 16));
}


static TILED_GUID TILE_MAP[] = {
	[TILE_NONE] = 0,
	[TILE_GRASS_1] = 1,
	[TILE_GRASS_2] = 2,
	[TILE_GRASS_3] = 3,
	[TILE_RIVER_DR] = 4,
	[TILE_RIVER_DL] = 5,
	[TILE_RIVER_UR] = 22,
	[TILE_RIVER_UL] = 23,

	[TILE_WATER_DR] = 19,
	[TILE_WATER_LDR] = 20,
	[TILE_WATER_DL] = 21,
	[TILE_WATER_URD] = 37,
	[TILE_WATER] = 38,
	[TILE_WATER_ULD] = 39,
	[TILE_WATER_UR] = 55,
	[TILE_WATER_LUR] = 56,
	[TILE_WATER_UL] = 57,

	[TILE_RIVER_UD] = 58,
	[TILE_RIVER_LR] = 74,
	[TILE_WATER_RIVER_V] = 40,
	[TILE_RIVER_WATER_V] = 76,
	[TILE_WATER_RIVER_H] = 73,
	[TILE_RIVER_WATER_H] = 75,

	[TILE_WATER_CORNER_UL] = 91,
	[TILE_WATER_CORNER_UR] = 92,
	[TILE_WATER_CORNER_DR] = 93,
	[TILE_WATER_CORNER_DL] = 94,
};


static TILED_GUID MAPOBJECT_MAP[] = {
	[MAPOBJECT_NONE] = 0,
	[MAPOBJECT_TREE] = 95,
	[MAPOBJECT_FOREST] = 113,
	[MAPOBJECT_HILL] = 6,
	[MAPOBJECT_BLOCKADE_H] = 24,
	[MAPOBJECT_BLOCKADE_V] = 26,
	[MAPOBJECT_LIGHTS] = 8,
	[MAPOBJECT_CAR1] = 7,
	[MAPOBJECT_CAR2] = 25,

	[MAPOBJECT_ROAD_UNIT] = 109,
	[MAPOBJECT_ROAD_R] = 110,
	[MAPOBJECT_ROAD_LR] = 111,
	[MAPOBJECT_ROAD_L] = 112,
	[MAPOBJECT_ROAD_D] = 127,
	[MAPOBJECT_ROAD_UD] = 145,
	[MAPOBJECT_ROAD_U] = 163,

	[MAPOBJECT_ROAD_DR] = 128,
	[MAPOBJECT_ROAD_LDR] = 129,
	[MAPOBJECT_ROAD_DL] = 130,

	[MAPOBJECT_ROAD_URD] = 146,
	[MAPOBJECT_ROAD_CROSS] = 147,
	[MAPOBJECT_ROAD_ULD] = 148,

	[MAPOBJECT_ROAD_UR] = 164,
	[MAPOBJECT_ROAD_LUR] = 165,
	[MAPOBJECT_ROAD_UL] = 166,

	[MAPOBJECT_BRIDGE_H1] = 131,
	[MAPOBJECT_BRIDGE_H2] = 149,
	[MAPOBJECT_BRIDGE_V] = 167,
};

