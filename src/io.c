#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* io_readline(void) {
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) return NULL;

    // Remove o \n do final, se houver
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }

    // Aloca apenas o necessário
    char *res = malloc(strlen(buffer) + 1);
    if (res) strcpy(res, buffer);
    return res;
}

int io_parse_int(const char *str, int *out) {
    char *end;
    long val = strtol(str, &end, 10);
    if (end == str || *end != '\0') return 0; // Não leu nada ou sobrou lixo
    *out = (int)val;
    return 1;
}

int io_parse_coord(const char *str, int rows, int cols, int *r, int *c) {
    if (!str || strlen(str) < 2) return 0;

    // Parse da coluna (Letra)
    char letter = toupper(str[0]);
    if (letter < 'A' || letter > 'Z') return 0;
    int col_idx = letter - 'A';

    // Parse da linha (Número)
    int row_idx;
    if (!io_parse_int(&str[1], &row_idx)) return 0;
    row_idx--; // Usuário digita 1-based, sistema usa 0-based

    // Validação de limites
    if (col_idx < 0 || col_idx >= cols) return 0;
    if (row_idx < 0 || row_idx >= rows) return 0;

    *r = row_idx;
    *c = col_idx;
    return 1;
}