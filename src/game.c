#include "game.h"
#include "io.h"
#include "rnd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* helpers */
static Player* get_player(Game *g, int idx) { return (idx == 1) ? &g->p1 : &g->p2; }
static Player* get_opponent(Game *g, int idx) { return (idx == 1) ? &g->p2 : &g->p1; }

static void setup_player(Player *p, const char *name, int size, char pos_mode) {
    /* copia nome manualmente */
    int i=0;
    while (name[i] != '\0' && i < 31) { p->nickname[i] = name[i]; i++; }
    p->nickname[i] = '\0';

    board_init(&p->board, size, size);
    board_init(&p->shots, size, size);
    fleet_init_default(&p->fleet);
    p->shots_count = 0;
    p->hits_count = 0;

    if (pos_mode == 'A') {
        if (!fleet_auto_place(&p->fleet, &p->board)) {
            fprintf(stderr, "Erro: não foi possível posicionar frota automaticamente\n");
            exit(1);
        }
    } else {
        for (int si=0; si < p->fleet.count; ++si) {
            int placed = 0;
            while (!placed) {
                printf("[%s] Posicione o navio %s (tamanho %d)\n", p->nickname, p->fleet.ships[si].name, p->fleet.ships[si].length);
                board_print_own(&p->board);
                printf("Coordenada inicial (ex: A1): ");
                char *line = io_readline();
                int r,c;
                if (!io_parse_coord(line, p->board.rows, p->board.cols, &r, &c)) {
                    printf("Coordenada inválida.\n");
                    free(line);
                    continue;
                }
                free(line);
                printf("Orientação (H ou V): ");
                char *ol = io_readline();
                char ch = ol[0];
                free(ol);
                if (ch >= 'a' && ch <= 'z') ch = ch - ('a' - 'A');
                Orientation o = (ch == 'V') ? ORIENT_V : ORIENT_H;
                if (!fleet_place_ship(&p->fleet, &p->board, si, r, c, o)) {
                    printf("Não foi possível posicionar neste local. Tente outra posição.\n");
                    continue;
                }
                placed = 1;
            }
        }
    }
}

void game_init(Game *g, int size, const char *name1, const char *name2, char pos_mode) {
    g->board_size = size;
    g->current_player = 1;
    g->game_over = 0;
    setup_player(&g->p1, name1, size, pos_mode);
    setup_player(&g->p2, name2, size, pos_mode);
}

void game_free(Game *g) {
    board_free(&g->p1.board);
    board_free(&g->p1.shots);
    fleet_free(&g->p1.fleet);
    board_free(&g->p2.board);
    board_free(&g->p2.shots);
    fleet_free(&g->p2.fleet);
}

static Ship* find_ship_by_id(Fleet *f, int id) {
    return fleet_find_by_id(f, id);
}

static void do_shot(Player *attacker, Player *defender, int r, int c) {
    Cell *target = board_cell(&defender->board, r, c);
    Cell *map = board_cell(&attacker->shots, r, c);
    if (target == NULL || map == NULL) { printf("Coordenada fora do tabuleiro.\n"); return; }
    if (target->state == CELL_HIT || target->state == CELL_MISS) { printf("Posição já atacada.\n"); return; }
    attacker->shots_count++;
    if (target->ship_id != -1) {
        target->state = CELL_HIT;
        map->state = CELL_HIT;
        attacker->hits_count++;
        Ship *s = find_ship_by_id(&defender->fleet, target->ship_id);
        if (s) {
            s->hits++;
            printf("Resultado: ACERTOU no %s!\n", s->name);
            if (s->hits >= s->length) {
                printf("Resultado: AFUNDOU %s!\n", s->name);
            }
        } else {
            printf("Resultado: ACERTOU!\n");
        }
    } else {
        target->state = CELL_MISS;
        map->state = CELL_MISS;
        printf("Resultado: ÁGUA.\n");
    }
}

void game_loop(Game *g) {
    while (!g->game_over) {
        int idx = g->current_player;
        Player *cur = get_player(g, idx);
        Player *opp = get_opponent(g, idx);
        printf("\n-- Turno de %s --\n", cur->nickname);
        printf("Seu mapa de tiros:\n");
        board_print_masked(&cur->shots);
        printf("Digite coordenada do tiro (ex.: E5): ");
        char *ln = io_readline();
        int r,c;
        if (!io_parse_coord(ln, g->board_size, g->board_size, &r, &c)) {
            printf("Coordenada inválida. Tente novamente.\n");
            free(ln);
            continue;
        }
        free(ln);
        do_shot(cur, opp, r, c);
        if (fleet_all_sunk(&opp->fleet)) {
            printf("\n*** FIM DE JOGO ***\n");
            printf("Vencedor: %s\n", cur->nickname);
            printf("Tiros: %d | Acertos: %d | Precisão: %.1f%%\n",
                   cur->shots_count, cur->hits_count,
                   cur->shots_count == 0 ? 0.0 : (100.0 * cur->hits_count / cur->shots_count));
            printf("--- Estado final dos tabuleiros ---\n");
            printf("Tabuleiro de %s (seus navios):\n", cur->nickname);
            board_print_own(&cur->board);
            printf("Tabuleiro de %s (visão real):\n", opp->nickname);
            board_print_own(&opp->board);
            g->game_over = 1;
            break;
        }
        g->current_player = (g->current_player == 1) ? 2 : 1;
    }
}
