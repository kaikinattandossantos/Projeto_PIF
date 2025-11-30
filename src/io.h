#ifndef IO_H
#define IO_H

char* io_readline();
int io_parse_coord(const char *s, int maxrows, int maxcols, int *out_r, int *out_c);
int io_parse_int(const char *s, int *out_val);
char io_char_to_upper(char c);
int io_is_letter(char c);

#endif
