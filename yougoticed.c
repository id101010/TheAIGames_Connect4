#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>

/* Defines */
#define MAX_LENGTH      40
#define FIELD_WIDTH     7
#define FIELD_HEIGHT    6

/* Globals */
char input[MAX_LENGTH]; // Gets filled with stuff from stdin

typedef struct game_s { // Game object struct for settings, actions and updates
    // Startup stuff
    int timebank;
    int time_per_move;
    char *player_names;
    int your_botid;
    int field_columns;
    int field_rows;

    // Update stuff
    int round;
    char board [FIELD_WIDTH][FIELD_HEIGHT];
} game_t;

/* Prototypes */
char *get_line(char *s, size_t n, FILE *f);
void die(const char *message);
void parser(game_t *game);
void parse_settings(char *setting_string, game_t *game);
void parse_update(char *setting_string, game_t *game);
void do_action(game_t *game);

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
        if(!strncmp(input, "settings ", 9)) {
            parse_settings(input, game);
        }
        if(!strncmp(input, "update ", 7)) {
            parse_update(input, game);
        }
    }
}

/* Parse settings string and fill game object */
void parse_settings(char *setting_string, game_t *game)
{
    assert(setting_string != NULL);
    assert(game != NULL);

    // settings timebank 10000
    if (!strcmp(setting_string, "timebank")) {
        //game->timebank = atoi(value);
        return;
    }

    // settings time_per_move 500
    if (!strcmp(setting_string, "time_per_move")) {
        //game->time_per_move = atoi(value);
        return;
    }

    // settings player_names player1,player2
    if (!strcmp(setting_string, "player_names")) {
        return;
    }

    // settings your_bot player1
    if (!strcmp(setting_string, "your_bot")) {
        return;
    }

    // settings your_botid 1
    if (!strcmp(setting_string, "your_botid")) {
        //game->botid = atoi(value);
    }

    return;
}

/* Parse update string and update game object */
void parse_update(char *update_string, game_t *game)
{
    assert(game != NULL);
    assert(update_string != NULL);

    // update game
    if (strcmp(update_string, "game")) {
        return;
    }

    // update game round 1
    if (!strcmp(update_string, "round")) {
        return;
    }

    // update game move 1
    if (!strcmp(update_string, "move")) {
        return;
    }

    // update field
    if (!strcmp(update_string, "field")) {
        return;
    }

    return;
}

/* */
void do_action(game_t *game)
{
}

// Main routine
int main(int argc, char **argv)
{
    /* Game vars */
    bool done = false;      // done flag
    game_t game;            // game object

    do {
        // TODO: ... game loop
    } while(!done);

    exit(EXIT_SUCCESS);
}
