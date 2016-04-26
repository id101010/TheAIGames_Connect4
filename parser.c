#include"parser.h"

/* Globals */
char input[3][MAX_LENGTH];  // Holds arguments of the game engine
char line[MAX_LENGTH];      // Gets filled with a whole game line

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
                &game->field[0][0],
                &game->field[0][1],
                &game->field[0][2],
                &game->field[0][3],
                &game->field[0][4],
                &game->field[0][5],
                &game->field[0][6],

                // 5th row
                &game->field[1][0],
                &game->field[1][1],
                &game->field[1][2],
                &game->field[1][3],
                &game->field[1][4],
                &game->field[1][5],
                &game->field[1][6],

                // 4th row
                &game->field[2][0],
                &game->field[2][1],
                &game->field[2][2],
                &game->field[2][3],
                &game->field[2][4],
                &game->field[2][5],
                &game->field[2][6],

                // 3rd row
                &game->field[3][0],
                &game->field[3][1],
                &game->field[3][2],
                &game->field[3][3],
                &game->field[3][4],
                &game->field[3][5],
                &game->field[3][6],

                // 2nd row
                &game->field[4][0],
                &game->field[4][1],
                &game->field[4][2],
                &game->field[4][3],
                &game->field[4][4],
                &game->field[4][5],
                &game->field[4][6],

                // 1st row
                &game->field[5][0],
                &game->field[5][1],
                &game->field[5][2],
                &game->field[5][3],
                &game->field[5][4],
                &game->field[5][5],
                &game->field[5][6]);
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

    /* print the whole field */
    for(int i = 0; i < FIELD_HEIGHT; i++) {
        for(int j = 0; j < FIELD_WIDTH; j++) {
            fprintf(stdout, "%d ", game->field[i][j]);
        }

        fprintf(stdout, "\n\t\t\t");
    }

    fprintf(stdout, "\n-----------END GAME OBJ DUMP-----------");
}
