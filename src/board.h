#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef enum {
    CELL_WATER,
    CELL_SHIP,
    CELL_HIT,
    CELL_MISS
} CellState;

typedef struct {
    CellState state;
    int ship_id;
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells;
} Board;

// Funções principais
void board_init(Board *b, int rows, int cols);
void board_free(Board *b);
bool board_in_bounds(Board *b, int r, int c);

// Retorna ponteiro para uma célula
Cell *board_cell(Board *b, int r, int c);

// Impressão
void board_print_own(Board *b);
void board_print_masked(Board *b);

#endif
