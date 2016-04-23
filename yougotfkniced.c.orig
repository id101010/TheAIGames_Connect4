#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>

/* Defines */
#define MAX_LENGTH      40
#define FIELD_WIDTH     3
#define FIELD_HEIGHT    3

/* Globals */
char input[MAX_LENGTH]; // Gets filled with stuff from stdin

typedef struct gamesettings_s { // Game object struct for settings, actions and updates
    // Startup stuff
    int timebank;
    int time_per_move;
    char *player_names;
    int your_botid;
    int field_columns;
    int field_rows;

    // Update stuff
    int round;
    char board [FIELD_WIDTH][FIELD_HEIGHT]; // TicTacToe Matrix

    // Action stuff
    int move;
    int pace_disc;
} gamesettings_t;

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

/* Initialize the game->board */
void init_game->board(gamesettings_t *game)
{
    int i, j;

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            game->board[i][j] =  ' ';
        }
    }
}

/* Parse arguments from game engine */
void parser(void)
{
    if(get_line(input, MAX_LENGTH, stdin) != NULL) {
        if(!strstr(input, "settings")) {
            // TODO: Handle settings string
        }
        if(!strstr(input, "action")) {
            // TODO: Handle action string
        }
        if(!strstr(input, "update")) {
            // TODO: Handle update string
        }
    }
}

/* Get opponents move */
void get_opponent_move(gamesettings_t *game)
{
    int x, y;

    // Read X,Y coordinates here
    //scanf("%d%*c%d", &x, &y);

    x--;
    y--;

    if(game->board[x][y]!= ' ') {
        die("Invalid move");
    } else {
        matrx[x][y] = 'X';
    }
}

/* Calculate bot move using minmax*/
void get_bot_move(void)
{
    // TODO: Minmax logic goes here ... 

    if(i*j==9)  {
        die("draw");
    } else {
        game->board[i][j] = 'O';
    }
}

// Main routine
int main(int argc, char **argv)
{
    /* Game vars */
    bool done = false;      // done flag
    gamesettings_t game;    // game object

    /* init stuff */
    init_field(&game);      // Init the game game->board

    do {
        // TODO: ... game loop
    } while(!done);

    exit(EXIT_SUCCESS);
}
