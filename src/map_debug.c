#include "map_debug.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>


static Tile tile_grass() {
	int type = rand() % 100;
	if (type < 90)
		return TILE_GRASS_1;
	if (type % 2 == 0)
		return TILE_GRASS_2;
	return TILE_GRASS_3;
}

#define LINE_X(fn, from_x, to_x, y, pen) {\
	for (int i = from_x; i <= to_x; i++)\
		fn(&map, i, y, (pen));\
}

#define LINE_Y(fn, x, from_y, to_y, pen) {\
	for (int i = from_y; i <= to_y; i++)\
		fn(&map, x, i, (pen));\
}

#define FILL(fn, from_x, from_y, to_x, to_y, pen) {\
	for (int x = from_x; x <= to_x; x++)\
	for (int y = from_y; y <= to_y; y++)\
		fn(&map, x, y, (pen));\
}

Map map_debug_create() {
	srand(time(NULL));

	const int w = 16;
	const int h = 16;
	const int size = w * h;
	Map map = map_create(w, h);

	FILL(map_set_tile, 0, 0, 15, 15, tile_grass());

	
	map_set_object(&map, 2, 2, MAPOBJECT_ROAD_R);
	LINE_X(map_set_object, 2, 10, 5, MAPOBJECT_ROAD_LR);
	LINE_X(map_set_object, 2, 10, 6, MAPOBJECT_TREE);
	LINE_X(map_set_tile, 2, 4, 4, TILE_WATER);
	map_set_object(&map, 11, 2, MAPOBJECT_ROAD_L);

	return map;
}

#undef LINE_X
#undef LINE_Y
#undef FILL
