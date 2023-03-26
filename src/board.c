#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "error.h"

Board *new_board()
{
    Board *board = malloc(sizeof(Board));
    if (!board)
        err_quit("Failed to allocate memory!");
    init_board(board);
    return board;
}
void del_board(Board *board)
{
    if (board)
        free(board);
}

void init_board(Board *board)
{
    if (!board)
        return;
    for (int i = 0; i < 8; i++)
        memset(board->board[i], 0, 8);

    // the board is stored "upside down"
    for (int i = 0; i < 8; i++)
        board->board[0][i] = (Piece){SETUP[i], WHITE};
    for (int i = 0; i < 8; i++)
        board->board[1][i] = (Piece){PAWN, WHITE};

    for (int i = 0; i < 8; i++)
        board->board[7][i] = (Piece){SETUP[i], BLACK};
    for (int i = 0; i < 8; i++)
        board->board[6][i] = (Piece){PAWN, BLACK};
}
