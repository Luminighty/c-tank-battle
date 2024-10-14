#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int map_index(Map *map, int x, int y) {
	return map->w * y + x;
}


Map map_create(int w, int h) {
	Map map;
	map.w = w;
	map.h = h;
	map.tiles = malloc(w * h * sizeof(Tile));
	printf("map tiles: %p", map.tiles);
	printf("map size: %ld", w * h * sizeof(Tile));
	fflush(stdout);
	map.objects = malloc(w * h * sizeof(MapObject));
	memset(map.tiles, TILE_NONE, w * h * sizeof(Tile));
	memset(map.objects, MAPOBJECT_NONE, w * h * sizeof(MapObject));

	return map;
}


void map_destroy(Map* map) {
	free(map->objects);
	free(map->tiles);
}


void map_set_tile(Map *map, int x, int y, Tile tile) {
	map->tiles[map_index(map, x, y)] = tile;
}


void map_set_object(Map *map, int x, int y, MapObject object) {
	map->objects[map_index(map, x, y)] = object;
}


TileType map_get_tile(Map *map, int x, int y) {
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return TILETYPE_BLOCK;

	int index = map_index(map, x, y);
	
	switch (map->objects[index]) {
	case MAPOBJECT_TREE:
	case MAPOBJECT_FOREST:
		return TILETYPE_FOREST;
	case MAPOBJECT_BLOCKADE_H:
	case MAPOBJECT_BLOCKADE_V:
		return TILETYPE_BLOCK;
	case MAPOBJECT_HILL:
		return TILETYPE_HILL;
	case MAPOBJECT_NONE:
	case MAPOBJECT_LIGHTS:
		break;
	case MAPOBJECT_ROAD_UNIT:
	case MAPOBJECT_ROAD_R:
	case MAPOBJECT_ROAD_LR:
	case MAPOBJECT_ROAD_L:
	case MAPOBJECT_ROAD_D:
	case MAPOBJECT_ROAD_UD:
	case MAPOBJECT_ROAD_U:

	case MAPOBJECT_ROAD_DR:
	case MAPOBJECT_ROAD_LDR:
	case MAPOBJECT_ROAD_DL:
	case MAPOBJECT_ROAD_URD:
	case MAPOBJECT_ROAD_CROSS:
	case MAPOBJECT_ROAD_ULD:

	case MAPOBJECT_ROAD_UR:
	case MAPOBJECT_ROAD_LUR:
	case MAPOBJECT_ROAD_UL:

	case MAPOBJECT_BRIDGE_H1:
	case MAPOBJECT_BRIDGE_H2:
	case MAPOBJECT_BRIDGE_V:
		return TILETYPE_ROAD;
	};

	switch (map->tiles[index]) {
	case TILE_GRASS_1:
	case TILE_GRASS_2:
	case TILE_GRASS_3:
		return TILETYPE_GRASS;

	case TILE_RIVER_DR:
	case TILE_RIVER_DL:
	case TILE_RIVER_UR:
	case TILE_RIVER_UL:
	case TILE_RIVER_UD:
	case TILE_RIVER_LR:

	case TILE_RIVER_WATER_H:
	case TILE_WATER_RIVER_H:

	case TILE_RIVER_WATER_V:
	case TILE_WATER_RIVER_V:

	case TILE_WATER_DR:
	case TILE_WATER_LDR:
	case TILE_WATER_DL:
	case TILE_WATER_URD:
	case TILE_WATER:
	case TILE_WATER_ULD:
	case TILE_WATER_UR:
	case TILE_WATER_LUR:
	case TILE_WATER_UL:
	case TILE_WATER_CORNER_UL:
	case TILE_WATER_CORNER_UR:
	case TILE_WATER_CORNER_DL:
	case TILE_WATER_CORNER_DR:
		return TILETYPE_WATER;
	
	case TILE_NONE:
	default:
		return TILETYPE_BLOCK;
	}
}

