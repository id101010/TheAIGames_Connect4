#ifndef HATRED_H
#define HATRED_H

/* Includes */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>
#include<limits.h>

/* Defines */
//#define DEBUG

#define MAX_LENGTH      255
#define FIELD_WIDTH     7
#define FIELD_HEIGHT    6
#define DEPTH           5
#define FIELD           (FIELD_WIDTH * FIELD_HEIGHT)

/* Globals */
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
    int field[FIELD_HEIGHT][FIELD_WIDTH];
} game_t;

/* Prototypes */
void init_game(game_t *game);

#endif /* HATRED_H */
