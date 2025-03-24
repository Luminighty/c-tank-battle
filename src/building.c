#include "building.h"

#include <string.h>


Building building_create(BuildingType type, short owner, short x, short y) {
	Building building;
	building.building_type = type;
	building.x = x;
	building.y = y;
	building.owner = owner;
	memset(&building.capture, 0, sizeof(short) * 5);
	return building;
}

