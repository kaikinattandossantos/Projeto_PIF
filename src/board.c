#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board *board_init(int rows, int cols) {
    Board *b = malloc(sizeof(Board));
    b->rows = rows;
    b->cols = cols;
    b->cells = malloc(rows * cols * sizeof(Cell));

    for (int i = 0; i < rows * cols; i++) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }

    return b;
}

void board_free(Board *b) {
    if (!b) return;
    free(b->cells);
    free(b);
}

Cell *board_cell(Board *b, int r, int c) {
    return &b->cells[r * b->cols + c];
}
// Em src/board.c

void board_print_own(Board *b) {
    // Cabeçalho das letras (A B C...)
    printf("   ");
    for (int i = 0; i < b->cols; i++) printf("%c ", 'A' + i);
    printf("\n");

    for (int r = 0; r < b->rows; r++) {
        printf("%2d ", r + 1); // Número da linha
        for (int c = 0; c < b->cols; c++) {
            Cell *cel = board_cell(b, r, c);
            char out = '~';

            if (cel->state == CELL_HIT) out = 'X';
            else if (cel->state == CELL_MISS) out = '='; // Ou '.'
            else if (cel->state == CELL_SHIP) out = 'S'; // <--- O 'S' aqui!
            
            printf("%c ", out);
        }
        printf("\n");
    }
}

void board_print_masked(Board *b) {
    // Cabeçalho das letras (A B C...)
    printf("   ");
    for (int i = 0; i < b->cols; i++) printf("%c ", 'A' + i);
    printf("\n");

    for (int r = 0; r < b->rows; r++) {
        printf("%2d ", r + 1); // Número da linha
        for (int c = 0; c < b->cols; c++) {
            Cell *cel = board_cell(b, r, c);
            char out = '~';

            if (cel->state == CELL_HIT) out = 'X';
            else if (cel->state == CELL_MISS) out = '='; // Ou '.'
            // AQUI NÃO TEM O 'S' (é a visão mascarada)
            
            printf("%c ", out);
        }
        printf("\n");
    }
}
int board_in_bounds(Board *b, int r, int c) {
    if (!b) return 0;
    // Retorna 1 (verdadeiro) se estiver dentro dos limites, 0 se fora
    return (r >= 0 && r < b->rows && c >= 0 && c < b->cols);
}
