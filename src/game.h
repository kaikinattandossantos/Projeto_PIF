#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;    // Tabuleiro com os navios do jogador
    Board shots;    // Tabuleiro de tiros realizados (mapa de calor)
    Fleet fleet;
    char nickname[32];
    int shots_count;
    int hits_count;
} Player;

typedef struct {
    Player p1;
    Player p2;
    int current_player; // 1 ou 2
    int game_over;
    int board_size;
} Game;

void game_init(Game *g, int size, const char *name1, const char *name2, char pos_mode);
void game_loop(Game *g);
void game_free(Game *g);

#endif