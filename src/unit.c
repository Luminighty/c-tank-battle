#include "unit.h"
#include "unit_config.h"

Unit unit_create(UnitType type, int owner, int x, int y) {
	Unit unit;
	unit.unit_type = type;
	unit.owner = owner;
	unit.x = x;
	unit.y = y;
	unit.moved = false;
	unit.hp = unit_get_hp(type);
	return unit;
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
