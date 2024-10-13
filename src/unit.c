#include "unit.h"
#include "map.h"

Unit unit_create(UnitType type, int owner, int x, int y) {
	return (Unit){ type, owner, x, y };
}

Unit unit_infantry(int owner, int x, int y) {
	return unit_create(UNIT_INFANTRY, owner, x, y);
}

Unit unit_plane(int owner, int x, int y) {
	return unit_create(UNIT_PLANE, owner, x, y);
}

Unit unit_tank(int owner, int x, int y) {
	return unit_create(UNIT_TANK, owner, x, y);
}

Unit unit_boat(int owner, int x, int y) {
	return unit_create(UNIT_BOAT, owner, x, y);
}
