#include "fleet.h"
#include "rnd.h"
#include <stdlib.h>
#include <stdio.h>

/* Inicializa frota: 1x5,1x4,2x3,2x2 */
void fleet_init_default(Fleet *f) {
    f->count = 6;
    f->ships = (Ship*) malloc(f->count * sizeof(Ship));
    if (f->ships == NULL) { fprintf(stderr,"Erro: malloc frota\n"); exit(1); }
    /* demonstração de realloc (requisito) */
    Ship *tmp = (Ship*) realloc(f->ships, f->count * sizeof(Ship));
    if (tmp) f->ships = tmp;

    int idx = 0;

    /* Porta-aviões */
    {
        const char *s = "Porta-avioes";
        int i=0; for (; s[i] != '\0' && i < 19; ++i) f->ships[idx].name[i] = s[i];
        f->ships[idx].name[i] = '\0';
        f->ships[idx].length = 5;
        f->ships[idx].id = idx;
        idx++;
    }
    /* Encouraçado */
    {
        const char *s = "Encouracado";
        int i=0; for (; s[i] != '\0' && i < 19; ++i) f->ships[idx].name[i] = s[i];
        f->ships[idx].name[i] = '\0';
        f->ships[idx].length = 4;
        f->ships[idx].id = idx;
        idx++;
    }
    /* Cruzador x2 */
    for (int k=0;k<2;k++){
        const char *s = "Cruzador";
        int i=0; for (; s[i] != '\0' && i < 19; ++i) f->ships[idx].name[i] = s[i];
        f->ships[idx].name[i] = '\0';
        f->ships[idx].length = 3;
        f->ships[idx].id = idx;
        idx++;
    }
    /* Destroyer x2 */
    for (int k=0;k<2;k++){
        const char *s = "Destroyer";
        int i=0; for (; s[i] != '\0' && i < 19; ++i) f->ships[idx].name[i] = s[i];
        f->ships[idx].name[i] = '\0';
        f->ships[idx].length = 2;
        f->ships[idx].id = idx;
        idx++;
    }

    for (int i = 0; i < f->count; ++i) {
        f->ships[i].hits = 0;
        f->ships[i].placed = 0;
        f->ships[i].start_r = f->ships[i].start_c = -1;
        f->ships[i].orient = ORIENT_H;
    }
}

void fleet_free(Fleet *f) {
    if (f->ships) free(f->ships);
    f->ships = NULL;
    f->count = 0;
}

/* Checa se cabe e não há colisão */
static int can_place(Board *b, int r, int c, Orientation o, int len){
    for (int k=0;k<len;k++){
        int rr = r + (o==ORIENT_V ? k : 0);
        int cc = c + (o==ORIENT_H ? k : 0);
        if (!board_in_bounds(b, rr, cc)) return 0;
        Cell *cel = board_cell(b, rr, cc);
        if (cel->ship_id != -1) return 0;
    }
    return 1;
}

int fleet_place_ship(Fleet *f, Board *b, int ship_idx, int r, int c, Orientation o) {
    if (ship_idx < 0 || ship_idx >= f->count) return 0;
    Ship *s = &f->ships[ship_idx];
    if (!can_place(b, r, c, o, s->length)) return 0;
    for (int k=0;k<s->length;k++){
        int rr = r + (o==ORIENT_V ? k : 0);
        int cc = c + (o==ORIENT_H ? k : 0);
        Cell *cel = board_cell(b, rr, cc);
        cel->ship_id = s->id;
        cel->state = CELL_SHIP;
    }
    s->placed = 1;
    s->start_r = r;
    s->start_c = c;
    s->orient = o;
    return 1;
}

int fleet_auto_place(Fleet *f, Board *b) {
    for (int i=0;i<f->count;i++){
        int placed = 0;
        int attempts = 0;
        while (!placed && attempts < 1000) {
            attempts++;
            Orientation o = (rand_int_inclusive(0,1) == 0) ? ORIENT_H : ORIENT_V;
            int maxr = b->rows - (o==ORIENT_V ? f->ships[i].length - 1 : 0);
            int maxc = b->cols - (o==ORIENT_H ? f->ships[i].length - 1 : 0);
            if (maxr <= 0 || maxc <= 0) return 0;
            int r = rand_int_inclusive(0, maxr-1);
            int c = rand_int_inclusive(0, maxc-1);
            if (fleet_place_ship(f, b, i, r, c, o)) placed = 1;
        }
        if (!placed) return 0;
    }
    return 1;
}

int fleet_all_sunk(Fleet *f) {
    for (int i=0;i<f->count;i++){
        if (f->ships[i].hits < f->ships[i].length) return 0;
    }
    return 1;
}

Ship* fleet_find_by_id(Fleet *f, int id){
    for (int i=0;i<f->count;i++) if (f->ships[i].id == id) return &f->ships[i];
    return NULL;
}
