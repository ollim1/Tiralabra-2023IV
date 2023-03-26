#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "error.h"

Game *new_game(int)
{
    Board *board = new_board();
    Game *game = malloc(sizeof(Game));
    if (!board || !game)
        err_quit("Failed to allocate memory!");
    
    game->board = board;
    return game;
}
void del_game(Game *game)
{
    if (game) {
        del_board(game->board);
        free(game);
    }
}

