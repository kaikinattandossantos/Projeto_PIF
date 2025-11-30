#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void board_init(Board *b, int rows, int cols) {
    b->rows = rows;
    b->cols = cols;
    b->cells = malloc(rows * cols * sizeof(Cell));

    for (int i = 0; i < rows * cols; i++) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }
}

void board_free(Board *b) {
    free(b->cells);
    b->cells = NULL;
}

bool board_in_bounds(Board *b, int r, int c) {
    return (r >= 0 && r < b->rows && c >= 0 && c < b->cols);
}

Cell *board_cell(Board *b, int r, int c) {
    if (!board_in_bounds(b, r, c))
        return NULL;
    return &b->cells[r * b->cols + c];
}

void board_print_own(Board *b) {
    printf("  ");
    for (int c = 0; c < b->cols; c++)
        printf("%c ", 'A' + c);
    printf("\n");

    for (int r = 0; r < b->rows; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < b->cols; c++) {
            Cell *cel = board_cell(b, r, c);
            char out = '~';

            if (cel->state == CELL_HIT)          out = 'X';
            else if (cel->ship_id != -1)        out = 'S';
            else if (cel->state == CELL_MISS)    out = '.';

            printf("%c ", out);
        }
        printf("\n");
    }
}

void board_print_masked(Board *b) {
    printf("  ");
    for (int c = 0; c < b->cols; c++)
        printf("%c ", 'A' + c);
    printf("\n");

    for (int r = 0; r < b->rows; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < b->cols; c++) {
            Cell *cel = board_cell(b, r, c);
            char out = '~';

            if (cel->state == CELL_HIT)          out = 'X';
            else if (cel->state == CELL_MISS)    out = '.';

            printf("%c ", out);
        }
        printf("\n");
    }
}
