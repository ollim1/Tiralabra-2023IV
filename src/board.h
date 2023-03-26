#ifndef BOARD_H
#define BOARD_H

enum Type {
    NONE = 0,
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    KING
};
enum Color {
    BLACK = 1,
    WHITE
};

typedef struct piece_t {
    enum Type type;
    enum Color color;
} Piece;

const enum Type SETUP[] =
{
    ROOK, KNIGHT, BISHOP, KING,
    QUEEN, BISHOP, KNIGHT, ROOK
};

typedef struct chessboard_t {
    Piece board[8][8];
} Board;

Board *new_board();
void del_board(Board *);

void init_board(Board *board);
Piece move(Board *, char*);
#endif
