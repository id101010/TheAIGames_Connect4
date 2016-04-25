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
#define DEPTH           5
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
    int field[FIELD_HEIGHT][FIELD_WIDTH];
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
void rmv(int board[FIELD_HEIGHT][FIELD_WIDTH], int column);
int minimax(int board[FIELD_HEIGHT][FIELD_WIDTH], int depth, int turn);
int heuristic(int s[FIELD_HEIGHT][FIELD_WIDTH]);
int endgame(int s[FIELD_HEIGHT][FIELD_WIDTH], int player);
int put(int board[FIELD_HEIGHT][FIELD_WIDTH], int column, int player);

/* - Parser functions ---------------------------------------------------------------- */

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

    for(int i = 0; i < FIELD_HEIGHT; i++) {
        for(int j = 0; j < FIELD_WIDTH; j++) {
            game->field[i][j] = 0;
        }
    }
}

/* - AI functions -------------------------------------------------------------------- */

/* Random AI action for engine test */
void ai_action(char *str1, char *str2, game_t *game)
{
    /* action move */
    if (!strcmp(str1, "move")) {
        game->timebank = atoi(str2);
    }

    /* random move */
    //column = rand() % FIELD_WIDTH;
    //fprintf(stdout, "place_disc %d\n", column);

    /* minimax decision */
    int col=0, move=0, n=0, val = -10000-1;

    for(col=0; col < 7; col++) {
        if(game->field[6-1][col]==0) {
            put(game->field, col, 2);
            n = minimax(game->field, DEPTH, 2);
            if ( -n > val ) {
                val = -n;
                move = col;
            }
            rmv(game->field, col);
        }
    }

    fprintf(stdout, "place_disc %d\n", move);
}

/* set disc */
int put(int field[FIELD_HEIGHT][FIELD_WIDTH], int column, int player)
{
    int i;

    for(i = 0; i < FIELD_HEIGHT; i++) {
        if(field[i][column] == 0) {
            field[i][column] = player;
            return i+1;
        }
    }

    return i;
}

/* remove disc */
void rmv(int field[FIELD_HEIGHT][FIELD_WIDTH], int column)
{
    int i;

    for (i=FIELD_HEIGHT-1; i>=0; i--) {
        if (field[i][column] != 0) {
            field[i][column] = 0;
        }
    }
}

/*0=no, 1=your_bot, 2=opponent, 3=stalemate */
int endgame(int f[FIELD_HEIGHT][FIELD_WIDTH], int player)
{
    int i, j;

    //check horizontals
    for(i=0; i<6; i++)
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i][j+1]== player && f[i][j+2]== player && f[i][j+3]== player) {
                return player;
            }
        }

    //check verticals
    for(i=0; i<=6-4; i++)
        for(j=0; j<7; j++) {
            if(f[i][j]== player && f[i+1][j]== player && f[i+2][j]== player && f[i+3][j]== player ) {
                return player;
            }
        }

    //check main diagonals (\)
    for(i=6-1; i>=4-1; i--)
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i-1][j+1]== player && f[i-2][j+2]== player && f[i-3][j+3]== player) {
                return player;
            }
        }

    //check other diagonals (/)
    for(i=0; i<=6-4; i++)
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i+1][j+1]== player && f[i+2][j+2]== player && f[i+3][j+3]== player) {
                return player;
            }
        }

    //check if stalement
    for(i=0; i<7; i++)
        if(f[i][6-1]==0) {
            return 0;    //game haven't finished yet - there's at least one empty cell in a top of a row
        }

    return 3; //stalemate - board is full
}

/* Calculates the score of a move */
int heuristic(int f[FIELD_HEIGHT][FIELD_WIDTH])
{
    int result = 0;
    int i, j;

    //check horizontals
    for(i=0; i<6; i++)
        for(j=0; j<=7-4; j++) {
            if(f[i][j]!= 2 && f[i][j+1]!= 2 && f[i][j+2]!= 2 && f[i][j+3]!= 2) {
                result++;
            }
            if(f[i][j]!= 1 && f[i][j+1]!= 1 && f[i][j+2]!= 1 && f[i][j+3]!= 1) {
                result--;
            }
        }

    //check verticals
    for(i=0; i<=6-4; i++)
        for(j=0; j<7; j++) {
            if(f[i][j]!= 2 && f[i+1][j]!= 2 && f[i+2][j]!= 2 && f[i+3][j]!= 2 ) {
                result++;
            }
            if(f[i][j]!= 1 && f[i+1][j]!= 1 && f[i+2][j]!= 1 && f[i+3][j]!= 1 ) {
                result--;
            }
        }

    return result;
}

int minimax(int board[FIELD_HEIGHT][FIELD_WIDTH], int depth, int turn /*1 or 2*/)
{
    int n=0, e=0, col=0, best=0, player=0;

    if((e=endgame(board, player))) {
        if(e==3) {
            return 0;
        }
        if(e==turn) {
            return 10000;
        } else {
            return -10000;
        }
    }

    if(depth==0) {
        return ((turn==1) ? heuristic(board) : -heuristic(board));
    }

    best = -10000;

    for(col=0; col < 7; col++)     //check every move
        if(board[6-1][col]==0) {   //make sure column isn't empty
            put(board, col, turn);
            n = minimax(board, depth-1, 3-turn);
            if(turn==1) {
                if ( -n > best ) {
                    best = -n;
                }
            } else { //turn==2
                if ( -n > best ) {
                    best = -n;
                }
            }
            rmv(board, col);
        }

    return best;
}

/* - Main --------------------------------------------------------------------------- */

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
