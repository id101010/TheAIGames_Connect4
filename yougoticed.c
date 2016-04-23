#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>

/* Defines */
#define MAX_LENGTH      255
#define FIELD_WIDTH     7
#define FIELD_HEIGHT    6

/* Globals */
char input[3][MAX_LENGTH];  // Gets filled with stuff from stdin
char line[MAX_LENGTH];

typedef struct game_s {     // Game object struct for settings, actions and updates
    // Startup stuff
    int timebank;
    int time_per_move;
    char *player_names;
    int your_botid;
    int field_columns;
    int field_rows;
    // Update stuff
    int round;
    int field[FIELD_WIDTH * FIELD_HEIGHT];
} game_t;

/* Prototypes */
char *get_line(char *s, size_t n, FILE *f);
void die(const char *message);
void parser(game_t *game);
void parse_settings(char *str1, char *str2, game_t *game);
void parse_update(char *str1, char *str2, char *str3, game_t *game);
void ai_action(char *str1, char *str2, game_t *game);

/* Abort on failure */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("[ERROR] %s\n ", message);
    }

    exit(EXIT_FAILURE);
}

/* Read line from stdin (safe) */
char *get_line(char *s, size_t n, FILE *f)
{
    char *p = fgets(s, n, f);

    if(p != NULL) {
        strtok(s, "\n");
    }

    if(s[0] == '\n') {
        s[0] = 0;
    }

    return p;
}

/* Parse arguments from game engine */
void parser(game_t *game)
{
    if(get_line(input, MAX_LENGTH, stdin) != NULL) {
        // Handle settings instructions
        if(!strncmp(line, "settings ", 9)) {
            sscanf(&line[9], "%s %s", input[0], input[1]);
            parse_settings(input[0], input[1], game);
        }

        // Handle update instructions
        if(!strncmp(line, "update ", 7)) {
            sscanf(&line[7], "%s %s %s", input[0], input[1]);
            parse_update(input[0], input[1], input[2], game);
        }

        // Handle action instructions
        if(!strncmp(line, "action ", 7)) {
            sscanf(&line[7], "%s %s", input[0], input[1]);
            ai_action(input[0], input[1], game);
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

    // settings player_names player1,player2
    if (!strcmp(str1, "player_names")) {
        // I don't care...
        return;
    }

    // settings your_bot player1
    if (!strcmp(str1, "your_bot")) {
        // I already know...
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
        game->round = atoi(str2);
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
                game->field[41],
                game->field[40],
                game->field[39],
                game->field[38],
                game->field[37],
                game->field[36],
                game->field[35],

                // 5th row
                game->field[34],
                game->field[33],
                game->field[32],
                game->field[31],
                game->field[30],
                game->field[29],
                game->field[28],

                // 4th row
                game->field[27],
                game->field[26],
                game->field[25],
                game->field[24],
                game->field[23],
                game->field[22],
                game->field[21],

                // 3rd row
                game->field[20],
                game->field[19],
                game->field[18],
                game->field[17],
                game->field[16],
                game->field[15],
                game->field[14],

                // 2nd row
                game->field[13],
                game->field[12],
                game->field[11],
                game->field[10],
                game->field[9],
                game->field[8],
                game->field[7],

                // 1st row
                game->field[6],
                game->field[5],
                game->field[4],
                game->field[3],
                game->field[2],
                game->field[1],
                game->field[0]);
    }

    return;
}

/* */
void ai_action(char *str1, char *str2, game_t *game)
{

}

// Main routine
int main(int argc, char **argv)
{
    /* Game vars */
    bool done = false;      // done flag
    game_t game;            // game object

    do {
        // Game loop
        parser(&game);
    } while(!done);

    exit(EXIT_SUCCESS);
}
