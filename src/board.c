#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "error.h"

const char *pieceStrings[] = {
    "  ", "Bp", "Br", "Bb", "Bn", "Bq", "Bk",
    "  ", "Wp", "Wr", "Wb", "Wn", "Wq", "Wk"
};

const char *bgStrings[] = {
    "[40m", "[100m"
};

const enum Type SETUP[] =
{
    ROOK, KNIGHT, BISHOP, KING,
    QUEEN, BISHOP, KNIGHT, ROOK
};

void init_board(Board *board);
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            board->board[i][j] = (Piece){NONE, BLACK};
    }

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

void board_print(Board *board)
{
    if (!board)
        return;
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            int bgIdx = (x + y) % 2;
            Piece p = board->board[y][x];

            int stringIdx = p.type;
            if (p.color == WHITE)
                stringIdx += 7;

            printf("%c%s%s%c[0m", 27, bgStrings[bgIdx], pieceStrings[stringIdx], 27);
        }
        printf("\n");
    }
}
