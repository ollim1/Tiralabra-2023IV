#ifndef GAME_H
#define GAME_H
#include "board.h"

// the Position struct can also be used as a 
typedef struct position_t {
    int y;
    int x;
} Position;

typedef struct gamestate_t {
    int enPassant; // allows en passant; clear if active, set if a pawn has moved two squares
    Position passantPawn; // en passant destination: the square that was skipped over
    int whiteCastled; // white has castled
    int blackCastled; // black has castled
} GameState;

typedef struct game_t {
    Board *board;
    GameState *state;
} Game;

Game *new_game(int);
int game_run(Game *);
void del_game(Game *);
void game_print(Game *);
#endif
