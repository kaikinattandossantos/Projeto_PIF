#include "io.h"
#include <stdio.h>
#include <stdlib.h>

/* leitura dinâmica de linha com malloc/realloc */
char* io_readline() {
    int cap = 64;
    char *buf = (char*) malloc(cap);
    if (!buf) { fprintf(stderr,"Erro malloc io_readline\n"); exit(1); }
    int len = 0;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = (char*) realloc(buf, cap);
            if (!tmp) { free(buf); fprintf(stderr,"Erro realloc io_readline\n"); exit(1); }
            buf = tmp;
        }
        buf[len++] = (char) ch;
    }
    buf[len] = '\0';
    return buf;
}

char io_char_to_upper(char c) {
    if (c >= 'a' && c <= 'z') return (char)(c - ('a' - 'A'));
    return c;
}

int io_is_letter(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
    return 0;
}

/* parse int manual */
int io_parse_int(const char *s, int *out_val) {
    if (!s || s[0] == '\0') return 0;
    int i = 0;
    int sign = 1;
    if (s[i] == '+') i++;
    else if (s[i] == '-') { sign = -1; i++; }
    int val = 0;
    int any = 0;
    while (s[i] != '\0') {
        char ch = s[i++];
        if (ch < '0' || ch > '9') return 0;
        any = 1;
        val = val * 10 + (ch - '0');
    }
    if (!any) return 0;
    *out_val = val * sign;
    return 1;
}

/* parse coord: e.g. "B5" ou "b10", com espaços permitidos */
int io_parse_coord(const char *s, int maxrows, int maxcols, int *out_r, int *out_c) {
    if (!s) return 0;
    int i = 0;
    /* pular espaços */
    while (s[i] == ' ' || s[i] == '\t') i++;
    char ch = s[i];
    if (!io_is_letter(ch)) return 0;
    char up = io_char_to_upper(ch);
    int col = up - 'A';
    i++;
    while (s[i] == ' ' || s[i] == '\t') i++;
    int num = 0;
    int any = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        any = 1;
        num = num * 10 + (s[i] - '0');
        i++;
    }
    if (!any) return 0;
    int row = num - 1;
    if (row < 0 || row >= maxrows) return 0;
    if (col < 0 || col >= maxcols) return 0;
    *out_r = row;
    *out_c = col;
    return 1;
}
