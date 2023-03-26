#ifndef GAME_H
#define GAME_H
#include "board.h"

typedef struct game_t {
    Board *board;
} Game;

Game *new_game(int);
int run_game(Game *);
void del_game(Game *);
#endif
