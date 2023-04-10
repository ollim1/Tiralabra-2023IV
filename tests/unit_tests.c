#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/game.h"

START_TEST(test_game_initialized) {
    Game *game = NULL;
    game = new_game(2);
    ck_assert_ptr_ne(game, NULL);
}
END_TEST


