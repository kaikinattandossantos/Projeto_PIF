#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;
    Board shots;
    Fleet fleet;
    char nickname[32];
    int shots_count;
    int hits_count;
} Player;

typedef struct {
    Player p1, p2;
    int current_player; /* 1 or 2 */
    int board_size;
    int game_over;
} Game;

void game_init(Game *g, int size, const char *name1, const char *name2, char pos_mode);
void game_free(Game *g);
void game_loop(Game *g);

#endif
