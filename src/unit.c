#include "unit.h"
#include "game.h"
#include "unit_config.h"
#include "vector.h"

Unit unit_create(UnitType type, short owner, short x, short y) {
	Unit unit;
	unit.unit_type = type;
	unit.owner = owner;
	unit.x = x;
	unit.y = y;
	unit.moved = false;
	unit.hp = unit_get_hp(type);
	return unit;
}

VECTOR_IMPL(UnitVec, Unit, unit_vec, 64);
