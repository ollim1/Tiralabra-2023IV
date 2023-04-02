#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "game.h"
#include "error.h"

const int DIAGONAL_MATRIX[][15] = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,},
    {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,},
    {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,},
    {0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,},
    {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,},
    {0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,},
    {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,},
    {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
};
const int CARDINAL_MATRIX[][15] = {
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,},
};
const int KNIGHT_MATRIX[][5] = {
    {0,1,0,1,0,},
    {1,0,0,0,1,},
    {0,0,0,0,0,},
    {1,0,0,0,1,},
    {0,1,0,1,0,},
};
const int WHITE_PAWN_MATRIX[][3] = {
    {0,0,0,},
    {1,1,1,},
    {0,1,0,},
};
const int BLACK_PAWN_MATRIX[][3] = {
    {0,1,0,},
    {1,1,1,},
    {0,0,0,},
};
const int KING_MATRIX[][3] = {
    {1,1,1,},
    {1,0,1,},
    {1,1,1,},
};

Game *new_game(int players)
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

void game_print(Game *game)
{
    board_print(game->board);
}

void game_move(Game *game, Position start, Position end)
{
}

int isLegal(Game *game, Position start, Position end)
{
    Piece piece = game->board->board[start.y][start.x];
    Position delta = {end.y - start.y, end.x - start.y};
    if (end.x > 7 || end.y > 7 || end.x < 0 || end.y < 0)
        return 0;
    switch (piece.type) {
        case NONE:
            return 0;
            break;
        case PAWN:
            /*
             * Pawn: can move one space forward.
             * Can move two positions if not previously moved. In this case, it can be captured by another pawn that moves into the space the pawn skipped.
             * Can capture one space forward diagonally.
             */
            if (delta.x < -1 || delta.y < 0 || delta.x > 1 || delta.y > 2)
                return 0;

            if (piece.color == BLACK && !BLACK_PAWN_MATRIX[delta.y + 1][delta.x + 1])
                return 0;
            else if (!WHITE_PAWN_MATRIX[delta.y + 1][delta.x + 1])
                return 0;

            if (game->state->enPassant) {

            }
            break;
        case ROOK:
            return CARDINAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case KNIGHT:
            if (delta.x < -2 || delta.y < -2 || delta.x > 2 || delta.y > 2)
                return 0;
            return KNIGHT_MATRIX[delta.y + 2][delta.x + 2];
            break;
        case BISHOP:
            return DIAGONAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case QUEEN:
            return DIAGONAL_MATRIX[delta.y + 7][delta.x + 7]
                || CARDINAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case KING:
            if (delta.y < -1 || delta.x < -1 || delta.y > 1 || delta.x > 1)
                return 0;
            return KING_MATRIX[delta.y + 1][delta.x + 1];
            break;
        default:
            break;
    }
    return 0;
}
