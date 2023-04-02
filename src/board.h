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
    BLACK,
    WHITE
};

typedef struct piece_t {
    enum Type type;
    enum Color color;
} Piece;

typedef struct board_t {
    Piece board[8][8];
} Board;

Board *new_board();
void del_board(Board *);

void board_print(Board *);
Piece move(Board *, char*);
#endif
