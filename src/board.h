#ifndef BOARD_H
#define BOARD_H

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
    int rows;
    int cols;
    Cell *cells;
} Board;

Board *board_init(int rows, int cols);
void board_free(Board *b);

Cell *board_cell(Board *b, int r, int c);

void board_print_own(Board *b);
void board_print_masked(Board *b);
int board_in_bounds(Board *b, int r, int c);

#endif
