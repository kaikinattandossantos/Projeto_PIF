#ifndef IO_H
#define IO_H

#include <stdio.h>

// Lê uma linha inteira de input, removendo o \n final.
// Retorna uma string alocada (deve ser liberada com free) ou NULL em erro/EOF.
char* io_readline(void);

// Converte string "10" para int. Retorna 1 se sucesso, 0 se falha.
int io_parse_int(const char *str, int *out);

// Converte "A5", "b10" para índices (row, col). Retorna 1 se sucesso.
// Valida se está dentro de rows/cols.
int io_parse_coord(const char *str, int rows, int cols, int *r, int *c);

#endif