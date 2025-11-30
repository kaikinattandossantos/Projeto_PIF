#ifndef FLEET_H
#define FLEET_H

#include "board.h"

typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    char name[20];
    int length;
    int hits;
    int placed;
    int id;
    int start_r, start_c;
    Orientation orient;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

void fleet_init_default(Fleet *f);
void fleet_free(Fleet *f);
int fleet_place_ship(Fleet *f, Board *b, int ship_idx, int r, int c, Orientation o);
int fleet_auto_place(Fleet *f, Board *b);
int fleet_all_sunk(Fleet *f);
Ship* fleet_find_by_id(Fleet *f, int id);

#endif
