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
const int PAWN_MATRICES[][5][3] = {
    {{0},{0},{0},{0},{0},},
    {
        {0,0,0,},
        {0,0,0,},
        {0,0,0,},
        {0,1,0,},
        {0,1,0,},
    }, {
        {0,1,0,},
        {0,1,0,},
        {0,0,0,},
        {0,0,0,},
        {0,0,0,},
    }
};
const int PAWN_CAPTURE_MATRICES[][5][3] = {
    {{0},{0},{0},},
    {
        {0,0,0,},
        {0,0,0,},
        {0,0,0,},
        {1,0,1,},
        {0,0,0,},
    }, {
        {0,0,0,},
        {1,0,1,},
        {0,0,0,},
        {0,0,0,},
        {0,0,0,},
    }
};
const int KING_MATRIX[][3] = {
    {1,1,1,},
    {1,0,1,},
    {1,1,1,},
};

int position_equals(Position a, Position b);
int isLegal(Game *game, Position start, Position end);
int safe(Game *, Position, enum Color);
void updateSafeSpaces(enum Color);

Game *new_game(int players)
{
    Board *board = new_board();
    Game *game = malloc(sizeof(Game));
    if (!board || !game)
        err_quit("Failed to allocate memory!");

    game->board = board;
    return game;
}

GameState *new_gamestate()
{
    GameState *gs = malloc(sizeof(GameState));
    if (!gs)
        return NULL;

    gs->enPassant = 0;
    gs->passedSpace = (Position){-1,-1};
    gs->whiteCastled = 0;
    gs->whiteCastled = 0;
    return gs;
}

void del_game(Game *game)
{
    if (game) {
        del_board(game->board);
        free(game->state);
        free(game);
    }
}

void game_print(Game *game)
{
    board_print(game->board);
}

void game_move(Game *game, Position start, Position end)
{
    if (isLegal(game, start, end)) {
        game->board->board[end.y][end.x] = game->board->board[start.y][start.x];
        game->board->board[start.y][start.x] = (Piece){NONE, EMPTY};
        updateSafeSpaces(game->board->board[start.y][start.x].color);
    }
}

int isLegal(Game *game, Position start, Position end)
{
    Piece piece = game->board->board[start.y][start.x];
    Piece dest = game->board->board[end.y][end.x];
    Position delta = {end.y - start.y, end.x - start.y};
    if (end.x > 7 || end.y > 7 || end.x < 0 || end.y < 0)
        return 0;
    if (dest.color == piece.color)
        return 0;

    switch (piece.type) {
        case NONE:
            return 0;
            break;
        case PAWN:
            /*
             * Pawn: can move one space forward.
             * Can move two positions if not previously moved. In this case,
             * it can be captured by another pawn that moves into the space the
             * pawn skipped.
             * Can capture one space forward diagonally.
             * Funny how this is the most complicated piece to implement...
             */
            if (delta.x < -1 || delta.y < -2 || delta.x > 1 || delta.y > 2)
                return 0;

            if (PAWN_CAPTURE_MATRICES[piece.color][delta.y + 2][delta.x + 1]) {
                if (dest.type == NONE) {
                    if (game->state->enPassant) {
                        if (position_equals(end, game->state->passedSpace))
                            return 1;
                        else
                            return 0;
                    }
                } else
                    return 1;
            }

            return 0;
            break;
        case ROOK:
            /*
             * Rook: can move any number of spaces in a cardinal direction.
             */
            return CARDINAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case KNIGHT:
            /*
             * Knight: moves and captures two spaces to any cardinal direction
             * and one to the side of that direction.
             */
            if (delta.x < -2 || delta.y < -2 || delta.x > 2 || delta.y > 2)
                return 0;
            return KNIGHT_MATRIX[delta.y + 2][delta.x + 2];
            break;
        case BISHOP:
            /*
             * Bishop: moves and captures diagonally.
             */
            return DIAGONAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case QUEEN:
            /*
             * Queen: moves and captures in any ordinal or cardinal direction.
             */
            return DIAGONAL_MATRIX[delta.y + 7][delta.x + 7]
                || CARDINAL_MATRIX[delta.y + 7][delta.x + 7];
            break;
        case KING:
            /*
             * King: moves and captures in any ordinal or cardinal direction,
             * but only one space away.
             */
            if (delta.y < -1 || delta.x < -1 || delta.y > 1 || delta.x > 1)
                return 0;
            return KING_MATRIX[delta.y + 1][delta.x + 1]
                && dest.type == NONE
                && safe(game, end, piece.color);
            break;
        default:
            break;
    }
    return 0;
}

int safe(Game *game, Position pos, enum Color color)
{
    /*
     * Check if a space is under attack.
     * Mark every space reachabla by every enemmy piece first. Doing this
     * efficiently will require storing results on every turn.
     */

    return 1;
}

void updateSafeSpaces(enum Color)
{

}

int position_equals(Position a, Position b)
{
    return a.x == b.x && a.y == b.y;
}
