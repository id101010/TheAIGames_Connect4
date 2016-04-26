#ifndef MINIMAX_H
#define MINIMAX_H

/* Includes */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include"hatred.h"

/* Defines */
#define DEPTH   5

/* Prototypes */
void rmv(int board[FIELD_HEIGHT][FIELD_WIDTH], int column);
void ai_action(char *str1, char *str2, game_t *game);
int minimax(int board[FIELD_HEIGHT][FIELD_WIDTH], int depth, int turn);
int heuristic(int s[FIELD_HEIGHT][FIELD_WIDTH]);
int endgame(int s[FIELD_HEIGHT][FIELD_WIDTH], int player);
int put(int board[FIELD_HEIGHT][FIELD_WIDTH], int column, int player);

#endif /* MINIMAX_H */
