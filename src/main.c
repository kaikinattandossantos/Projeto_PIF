#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "io.h"
#include "rnd.h"

int main() {
    rnd_init();
    printf("=== BATALHA NAVAL ===\n");
    int running = 1;
    int board_size = 10;
    char pos_mode = 'A';

    while (running) {
        printf("\n1) Novo jogo\n2) Configurações\n3) Sair\n> ");
        char *opt = io_readline();
        if (!opt) break;
        if (opt[0] == '3' || opt[0] == 's' || opt[0] == 'S') { free(opt); break; }
        else if (opt[0] == '2') {
            printf("Tamanho do tabuleiro (6-26) - atual %d\n> ", board_size);
            char *ln = io_readline();
            int v;
            if (io_parse_int(ln, &v) && v >= 6 && v <= 26) board_size = v;
            else printf("Valor inválido, mantendo %d\n", board_size);
            free(ln);
            printf("Posicionamento (M)anual ou (A)utomático? (atual %c)\n> ", pos_mode);
            char *pm = io_readline();
            if (pm[0] == 'M' || pm[0] == 'm') pos_mode = 'M';
            else pos_mode = 'A';
            free(pm);
            free(opt);
            continue;
        } else {
            printf("Informe apelido do Jogador 1: ");
            char *n1 = io_readline();
            printf("Informe apelido do Jogador 2: ");
            char *n2 = io_readline();
            printf("Tamanho do tabuleiro (6-26) - Enter para usar %d\n> ", board_size);
            char *ln = io_readline();
            if (ln[0] != '\0') {
                int v; if (io_parse_int(ln, &v) && v >= 6 && v <= 26) board_size = v;
                else printf("Entrada inválida. Usando %d\n", board_size);
            }
            free(ln);
            printf("Posicionamento (M)anual ou (A)utomático? (%c)\n> ", pos_mode);
            char *pm = io_readline();
            if (pm[0] == 'M' || pm[0] == 'm') pos_mode = 'M';
            else pos_mode = 'A';
            free(pm);
            Game g;
            game_init(&g, board_size, n1, n2, pos_mode);
            free(n1); free(n2);
            game_loop(&g);
            game_free(&g);
            free(opt);
            printf("Jogo terminado.\n");
        }
    }
    return 0;
}
