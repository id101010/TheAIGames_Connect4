#ifndef CONNECT4BOT_H
#define CONNECT4BOT_H

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
#define MAX_LENGTH  255
#define F_COLS      7
#define F_ROWS      6
#define FIELD       (F_COLS * F_ROWS)

/* Globals */
typedef struct game_s {                 // Game object struct for settings, actions and updates
    /* Settings */
    int timebank;                       // amount of time left
    int time_per_move;                  // amount of time per move
    char player_names[MAX_LENGTH];      // player names (comma separated)
    char your_bot[MAX_LENGTH];          // name of your bot
    int your_botid;                     // ID of your bot (1 or 2)
    int field_columns;                  // number of columns
    int field_rows;                     // number of rows
    /* Updates */
    int round;                          // round number
    int field[F_ROWS][F_COLS];          // field array
} game_t;

/* Prototypes */
void init_game(game_t *game);

#endif /* CONNECT4BOT_H */
