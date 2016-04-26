#include"hatred.h"
#include"parser.h"

/* Defines */
//#define DEBUG

/* Globals */

void init_game(game_t *game)
{
    /* init random number generator */
    srand(time(NULL));

    /* init game object */
    game->timebank = 0;
    game->time_per_move = 0;
    strcpy(game->player_names, "player1,player2");
    strcpy(game->your_bot, "player1");
    game->your_botid = 0;
    game->field_columns = 0;
    game->field_rows = 0;
    game->round = 0;

    for(int i = 0; i < FIELD_HEIGHT; i++) {
        for(int j = 0; j < FIELD_WIDTH; j++) {
            game->field[i][j] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    /* Game vars */
    bool done = false;      // done flag
    game_t game;            // game object

    /* Init game object */
    init_game(&game);

    /* Game loop */
    do {
        parser(&game);
    } while(!done);

    exit(EXIT_SUCCESS);
}
