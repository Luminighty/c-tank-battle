#include "render.h"
#include "game.h"
#include "gamestate.h"
#include "map.h"
#include "pathfinder.h"
#include "raylib.h"
#include "sprite.h"
#include "unit.h"


#define SPRITE(x, y) ((Rectangle){ (x) * 16, (y) * 16, 16, 16})
#define UNIT(x) SPRITE(5 + (x), 5)

static const Rectangle UNIT_MAP[];
static const Rectangle TILE_MAP[];
static const Rectangle MAPOBJECT_MAP[];

static void render_map(Map* map);
static void render_unit_selected();

void render() {
	BeginDrawing();
	BeginMode2D(game.camera);
	ClearBackground(RAYWHITE);

	render_map(&game.map);

	switch (game.gamestate.type) {
	case GAMESTATE_UNIT_SELECTED:
		render_unit_selected();
		break;
	default:
		break;
	}

	for (int i = 0; i < game.unit_count; i++) {
		Unit* unit = &game.units[i];
		Rectangle source = UNIT_MAP[unit->unit_type];
		source.y += unit->owner * 16;
		Vector2 position = { unit->x, unit->y };
		DrawTextureRec(texture_tilemap, source, position, WHITE);
	}

	Vector2 cursor_position = { game.cursor.x * 16, game.cursor.y * 16 };
	DrawTextureRec(texture_tilemap, SPRITE(7, 3), cursor_position, WHITE);

	EndMode2D();
	EndDrawing();
}

static void render_unit_selected() {
	PathFinderResult* result = &game.gamestate.unit_selected.movement_result;
	for (int i = 0; i < result->node_count; i++) {
		Vector2 position = { result->nodes[i].x * 16, result->nodes[i].y * 16 };
		DrawTextureRec(texture_tilemap, SPRITE(7, 4), position, WHITE);
	}
}

static void render_map(Map* map) {
	for (int x = 0; x < map->w; x++) {
		for (int y = 0; y < map->h; y++) {
			int index = y * map->w + x;
			Rectangle source = TILE_MAP[map->tiles[index]];
			Vector2 position = { x * 16, y * 16 };
			DrawTextureRec(texture_tilemap, source, position, WHITE);
		}
	}
	for (int x = 0; x < map->w; x++) {
		for (int y = 0; y < map->h; y++) {
			int index = y * map->w + x;
			MapObject object = map->objects[index];
			if (object == MAPOBJECT_NONE)
				continue;
			Rectangle source = MAPOBJECT_MAP[map->objects[index]];
			Vector2 position = { x * 16, y * 16 };
			DrawTextureRec(texture_tilemap, source, position, WHITE);
		}
	}
}

static const Rectangle UNIT_MAP[] = {
	[UNIT_INFANTRY] = UNIT(11),
	[UNIT_TANK] = UNIT(3),
	[UNIT_BOAT] = UNIT(8),
	[UNIT_PLANE] = UNIT(5),
};

static const Rectangle TILE_MAP[] = {
    [TILE_GRASS_1] = SPRITE(0, 0),
    [TILE_GRASS_2] = SPRITE(1, 0),
    [TILE_GRASS_3] = SPRITE(2, 0),

    [TILE_RIVER_DR] = SPRITE(3, 0),
    [TILE_RIVER_DL] = SPRITE(4, 0),
    [TILE_RIVER_UR] = SPRITE(3, 1),
    [TILE_RIVER_UL] = SPRITE(4, 1),
    [TILE_RIVER_UD] = SPRITE(3, 3),
    [TILE_RIVER_LR] = SPRITE(1, 4),

    [TILE_RIVER_WATER_H] = SPRITE(2, 4),
    [TILE_WATER_RIVER_H] = SPRITE(0, 4),

    [TILE_RIVER_WATER_V] = SPRITE(3, 2),
    [TILE_WATER_RIVER_V] = SPRITE(3, 4),

    [TILE_WATER_DR] = SPRITE(0, 1),
    [TILE_WATER_LDR] = SPRITE(1, 1),
    [TILE_WATER_DL] = SPRITE(2, 1),
    [TILE_WATER_URD] = SPRITE(0, 2),
    [TILE_WATER] = SPRITE(1, 2),
    [TILE_WATER_ULD] = SPRITE(2, 2),
    [TILE_WATER_UR] = SPRITE(0, 3),
    [TILE_WATER_LUR] = SPRITE(1, 3),
    [TILE_WATER_UL] = SPRITE(2, 3),
    [TILE_WATER_CORNER_UL] = SPRITE(0, 5),
    [TILE_WATER_CORNER_UR] = SPRITE(1, 5),
    [TILE_WATER_CORNER_DL] = SPRITE(2, 5),
    [TILE_WATER_CORNER_DR] = SPRITE(3, 5),
};

static const Rectangle MAPOBJECT_MAP[] = {
    [MAPOBJECT_TREE] = SPRITE(4, 5),
    [MAPOBJECT_FOREST] = SPRITE(4, 6),
    [MAPOBJECT_HILL] = SPRITE(5, 0),
    [MAPOBJECT_BLOCKADE_H] = SPRITE(5, 1),
    [MAPOBJECT_BLOCKADE_V] = SPRITE(7, 1),
    [MAPOBJECT_LIGHTS] = SPRITE(7, 0),
    [MAPOBJECT_ROAD_UNIT] = SPRITE(0, 6),

    [MAPOBJECT_ROAD_R] = SPRITE(1, 6),
    [MAPOBJECT_ROAD_LR] = SPRITE(2, 6),
    [MAPOBJECT_ROAD_L] = SPRITE(3, 6),
    [MAPOBJECT_ROAD_D] = SPRITE(0, 7),
    [MAPOBJECT_ROAD_UD] = SPRITE(0, 8),
    [MAPOBJECT_ROAD_U] = SPRITE(0, 9),

    [MAPOBJECT_ROAD_DR] = SPRITE(1, 7),
    [MAPOBJECT_ROAD_LDR] = SPRITE(2, 7),
    [MAPOBJECT_ROAD_DL] = SPRITE(3, 7),

    [MAPOBJECT_ROAD_URD] = SPRITE(1, 8),
    [MAPOBJECT_ROAD_CROSS] = SPRITE(2, 8),
    [MAPOBJECT_ROAD_ULD] = SPRITE(3, 8),

    [MAPOBJECT_ROAD_UR] = SPRITE(1, 9),
    [MAPOBJECT_ROAD_LUR] = SPRITE(2, 9),
    [MAPOBJECT_ROAD_UL] = SPRITE(3, 9),

    [MAPOBJECT_BRIDGE_H1] = SPRITE(4, 7),
    [MAPOBJECT_BRIDGE_H2] = SPRITE(4, 8),
    [MAPOBJECT_BRIDGE_V] = SPRITE(4, 9),
};

