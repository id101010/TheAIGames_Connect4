#ifndef MINIMAX_H
#define MINIMAX_H

/* Includes */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include"connect4bot.h"

/* Defines */
#define DEPTH   7

/* Prototypes */
void rmv(int board[F_ROWS][F_COLS], int column);
void ai_action(char *str1, char *str2, game_t *game);
void random_move(char *str1, char *str2, game_t *game);
int minimax(int board[F_ROWS][F_COLS], int depth, int turn);
int heuristic(int s[F_ROWS][F_COLS]);
int endgame(int s[F_ROWS][F_COLS], int player);
int put(int board[F_ROWS][F_COLS], int column, int player);

#endif /* MINIMAX_H */
