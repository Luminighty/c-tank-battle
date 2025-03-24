#ifndef BUILDING_H
#define BUILDING_H


typedef enum {
    BUILDING_CITY1,
    BUILDING_HQ,
    BUILDING_CITY2,
    BUILDING_BASE,
    BUILDING_PORT,
    BUILDING_COMMS,
    BUILDING_SILO,
    BUILDING_AIRPORT,
    BUILDING_FLAG
} BuildingType;


typedef struct {
    BuildingType building_type;
    short owner;
    short capture[5];
    short x;
    short y;
} Building;


Building building_create(BuildingType type, short owner, short x, short y);

#endif // BUILDING_H
