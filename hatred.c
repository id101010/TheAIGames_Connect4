#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>
#include<limits.h>

/* Defines */
#define MAX_LENGTH      255
#define FIELD_WIDTH     7
#define FIELD_HEIGHT    6
#define FIELD           (FIELD_WIDTH * FIELD_HEIGHT)
//#define DEBUG

/* Globals */
char input[3][MAX_LENGTH];  // Gets filled with stuff from stdin
char line[MAX_LENGTH];

typedef struct game_s {     // Game object struct for settings, actions and updates
    /* Settings */
    int timebank;
    int time_per_move;
    char player_names[MAX_LENGTH];
    char your_bot[MAX_LENGTH];
    int your_botid;
    int field_columns;
    int field_rows;
    /* Updates */
    int round;
    int field[FIELD];
} game_t;

/* Prototypes */
char *get_line(char *s, size_t n, FILE *f);
void die(const char *message);
void parser(game_t *game);
void parse_settings(char *str1, char *str2, game_t *game);
void parse_update(char *str1, char *str2, char *str3, game_t *game);
void ai_action(char *str1, char *str2, game_t *game);
void debug_print(game_t *game);
void init_game(game_t *game);

/* Abort on failure */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        fprintf(stderr, "[ERROR] %s\n ", message);
    }

    exit(EXIT_FAILURE);
}

/* Read line from stdin (safe) */
char *get_line(char *string, size_t size, FILE *file)
{
    char *buffer = fgets(string, size, file);

    if(buffer != NULL) {
        strtok(string, "\n");
    }

    if(string[0] == '\n') {
        string[0] = 0;
    }

    return buffer;
}

/* Parse arguments from game engine */
void parser(game_t *game)
{
    if(get_line(line, MAX_LENGTH, stdin) != NULL) {
        // Handle settings instructions
        if(!strncmp(line, "settings ", 9)) {
            sscanf(&line[9], "%s %s", input[0], input[1]);
            parse_settings(input[0], input[1], game);
#ifdef DEBUG
            debug_print(game);
#endif
        }

        // Handle update instructions
        if(!strncmp(line, "update ", 7)) {
            sscanf(&line[7], "%s %s %s", input[0], input[1], input[2]);
            parse_update(input[0], input[1], input[2], game);
#ifdef DEBUG
            debug_print(game);
#endif
        }

        // Handle action instructions
        if(!strncmp(line, "action ", 7)) {
            sscanf(&line[7], "%s %s", input[0], input[1]);
            ai_action(input[0], input[1], game);
            fflush(stdout); // Important!
#ifdef DEBUG
            debug_print(game);
#endif
        }
    }
}

/* Parse settings string and fill game object */
void parse_settings(char *str1, char *str2, game_t *game)
{
    assert(game != NULL);
    assert(str1 != NULL); // Setting type
    assert(str2 != NULL); // Value

    // settings timebank
    if (!strcmp(str1, "timebank")) {
        game->timebank = atoi(str2);
        return;
    }

    // settings time_per_move
    if (!strcmp(str1, "time_per_move")) {
        game->time_per_move = atoi(str2);
        return;
    }

    // settings player_names
    if (!strcmp(str1, "player_names")) {
        strcpy(game->player_names, str2);
        return;
    }

    // settings your_bot
    if (!strcmp(str1, "your_bot")) {
        strcpy(game->your_bot, str2);
        return;
    }

    // settings your_botid
    if (!strcmp(str1, "your_botid")) {
        game->your_botid = atoi(str2);
        return;
    }

    // settings field_columns
    if (!strcmp(str1, "field_columns")) {
        game->field_columns = atoi(str2);
        return;
    }

    // settings field_rows
    if (!strcmp(str1, "field_rows")) {
        game->field_rows = atoi(str2);
        return;
    }

    return;
}

/* Parse update string and update game object */
void parse_update(char *str1, char *str2, char *str3, game_t *game)
{
    assert(game != NULL);
    assert(str1 != NULL); // Game
    assert(str2 != NULL); // Updatetype
    assert(str3 != NULL); // Value

    // update game
    if (strcmp(str1, "game")) {
        // unknown game update, error
        return;
    }

    // update game round
    if (!strcmp(str2, "round")) {
        game->round = atoi(str3);
    }

    if(!strcmp(str2, "field")) {
        sscanf( str3,

                "%d,%d,%d,%d,%d,%d,%d;"
                "%d,%d,%d,%d,%d,%d,%d;"
                "%d,%d,%d,%d,%d,%d,%d;"
                "%d,%d,%d,%d,%d,%d,%d;"
                "%d,%d,%d,%d,%d,%d,%d;"
                "%d,%d,%d,%d,%d,%d,%d;",

                // 6th row
                &game->field[0],
                &game->field[1],
                &game->field[2],
                &game->field[3],
                &game->field[4],
                &game->field[5],
                &game->field[6],

                // 5th row
                &game->field[7],
                &game->field[8],
                &game->field[9],
                &game->field[10],
                &game->field[11],
                &game->field[12],
                &game->field[13],

                // 4th row
                &game->field[14],
                &game->field[15],
                &game->field[16],
                &game->field[17],
                &game->field[18],
                &game->field[19],
                &game->field[20],

                // 3rd row
                &game->field[21],
                &game->field[22],
                &game->field[23],
                &game->field[24],
                &game->field[25],
                &game->field[26],
                &game->field[27],

                // 2nd row
                &game->field[28],
                &game->field[29],
                &game->field[30],
                &game->field[31],
                &game->field[32],
                &game->field[33],
                &game->field[34],

                // 1st row
                &game->field[35],
                &game->field[36],
                &game->field[37],
                &game->field[38],
                &game->field[39],
                &game->field[40],
                &game->field[41]);
    }

    return;
}

/* Debug function which prints the contents of the game object */
void debug_print(game_t *game)
{
    fprintf(stdout, "\n---------BEGIN GAME OBJ DUMP-----------");
    fprintf(stdout, "\nsetting:timebank\t%d",      game->timebank);
    fprintf(stdout, "\nsetting:time_per_move\t%d", game->time_per_move);
    fprintf(stdout, "\nsetting:player_names\t%s",  game->player_names);
    fprintf(stdout, "\nsetting:your_bot\t%s",      game->your_bot);
    fprintf(stdout, "\nsetting:your_botid\t%d",    game->your_botid);
    fprintf(stdout, "\nsetting:field_columns\t%d", game->field_columns);
    fprintf(stdout, "\nsetting:field_rows\t%d",    game->field_rows);
    fprintf(stdout, "\nupdate:round\t\t%d",        game->round);
    fprintf(stdout, "\nupdate:field\t\t");

    for(int i = 0; i < FIELD; i++) {
        if(((i%7)==0) && (i>0)) {
            fprintf(stdout, "\n\t\t\t");
        }
        fprintf(stdout, "%d ", game->field[i]);
    }

    fprintf(stdout, "\n-----------END GAME OBJ DUMP-----------");
}

/* Init game object */
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

    for(int i = 0; i < FIELD; i++) {
        game->field[i] = 0;
    }
}

/* Random AI action for engine test */
void ai_action(char *str1, char *str2, game_t *game)
{
    int column = 0;

    // action move
    if (!strcmp(str1, "move")) {
        game->timebank = atoi(str2);
    }

    // random move
    column = rand() % FIELD_WIDTH;
    fprintf(stdout, "place_disc %d\n", column);
}

/* Calls the alpha-beta pruning algorithm */
int alpha_beta_search(game_t *game)
{
    return max_value(game, 0, INT_MIN, INT_MAX);
}

/* Returns the highest possible utility value */
int max_value(game_t *game, int depth, int alpha, int beta)
{
    return 0;
}

/* Main routine */
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
