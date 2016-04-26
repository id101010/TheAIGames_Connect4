#ifndef PARSER_H
#define PARSER_H

/* Includes */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include"hatred.h"
#include"minimax.h"

/* Defines */

/* Prototypes */
char *get_line(char *s, size_t n, FILE *f);
void die(const char *message);
void parser(game_t *game);
void parse_settings(char *str1, char *str2, game_t *game);
void parse_update(char *str1, char *str2, char *str3, game_t *game);
void debug_print(game_t *game);

#endif /* PARSER_H */
