#ifndef MAP_H
#define MAP_H

typedef enum {
    TILE_NONE,

    TILE_GRASS_1,
    TILE_GRASS_2,
    TILE_GRASS_3,

    TILE_RIVER_DR,
    TILE_RIVER_DL,
    TILE_RIVER_UR,
    TILE_RIVER_UL,
    TILE_RIVER_UD,
    TILE_RIVER_LR,

    TILE_RIVER_WATER_H,
    TILE_WATER_RIVER_H,

    TILE_RIVER_WATER_V,
    TILE_WATER_RIVER_V,

    TILE_WATER_DR,
    TILE_WATER_LDR,
    TILE_WATER_DL,
    TILE_WATER_URD,
    TILE_WATER,
    TILE_WATER_ULD,
    TILE_WATER_UR,
    TILE_WATER_LUR,
    TILE_WATER_UL,
    TILE_WATER_CORNER_UL,
    TILE_WATER_CORNER_UR,
    TILE_WATER_CORNER_DL,
    TILE_WATER_CORNER_DR,
    TILE_SIZE,
} Tile;

typedef enum {
    TILETYPE_GRASS,
    TILETYPE_FOREST,
    TILETYPE_WATER,
    TILETYPE_ROAD,
    TILETYPE_HILL,
    TILETYPE_BLOCK,
} TileType;

typedef enum {
    MAPOBJECT_NONE,
    MAPOBJECT_TREE,
    MAPOBJECT_FOREST,
    MAPOBJECT_HILL,
    MAPOBJECT_BLOCKADE_H,
    MAPOBJECT_BLOCKADE_V,
    MAPOBJECT_LIGHTS,

    MAPOBJECT_ROAD_UNIT,
    MAPOBJECT_ROAD_R,
    MAPOBJECT_ROAD_LR,
    MAPOBJECT_ROAD_L,
    MAPOBJECT_ROAD_D,
    MAPOBJECT_ROAD_UD,
    MAPOBJECT_ROAD_U,

    MAPOBJECT_ROAD_DR,
    MAPOBJECT_ROAD_LDR,
    MAPOBJECT_ROAD_DL,

    MAPOBJECT_ROAD_URD,
    MAPOBJECT_ROAD_CROSS,
    MAPOBJECT_ROAD_ULD,

    MAPOBJECT_ROAD_UR,
    MAPOBJECT_ROAD_LUR,
    MAPOBJECT_ROAD_UL,

    MAPOBJECT_BRIDGE_H1,
    MAPOBJECT_BRIDGE_H2,
    MAPOBJECT_BRIDGE_V,
    MAPOBJECT_SIZE,
} MapObject;

typedef struct  {
    int w;
    int h;
    Tile* tiles;
    MapObject* objects;
} Map;


Map map_create(int w, int h);
void map_destroy(Map* map);
void map_set_tile(Map* map, int x, int y, Tile tile);
void map_set_object(Map* map, int x, int y, MapObject tile);
TileType map_get_tile(Map* map, int x, int y);

#endif // MAP_H
