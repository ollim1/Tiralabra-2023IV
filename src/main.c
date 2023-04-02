#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include "game.h"
#include "error.h"

void run(int players);
int main(int argc, char **argv)
{
    int players = 1;
    int opt;

    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt)
        {
            case 'p':
                players = atoi(optarg); // number of human players, the rest is filled with computers
                break;
        }
    }
    if (players > 2 || players < 0)
        err_quit("invalid number of players");
    run(players);
}

void run(int players)
{
    Game *game = new_game(players);
    game_print(game);
    del_game(game);
    int result = 0;
    if (result == -1) {
        printf("Black wins!\n");
    } else if (result == 0) {
        printf("Draw!\n");
    } else {
        printf("White wins!\n");
    }
}
