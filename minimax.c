#include"minimax.h"

/* Random AI action for engine test */
void ai_action(char *str1, char *str2, game_t *game)
{
    int col=0, move=0, n=0, val = 10000-1;

    /* action move */
    if (!strcmp(str1, "move")) {
        game->timebank = atoi(str2);
    }

    /* random move */
    //column = rand() % F_COLS;
    //fprintf(stdout, "place_disc %d\n", column);

    /* minimax decision for each move on the field*/
    for(col = 0; col < F_COLS; col++) {
        if(game->field[F_ROWS-1][col]==0) {
            put(game->field, col, game->your_botid);
            n = minimax(game->field, DEPTH, game->your_botid);
            fprintf(stdout, "%d ", n);
            if ( n < val ) {
                val = n;
                move = col;
            }
            rmv(game->field, col);
        }
    }

    fprintf(stdout, "place_disc %d\n", move);
}

/* set disc */
int put(int field[F_ROWS][F_COLS], int column, int player)
{
    int i;

    for(i = 0; i < F_ROWS; i++) {
        if(field[i][column] == 0) {
            field[i][column] = player;
            return i+1;
        }
    }

    return i;
}

/* remove disc */
void rmv(int field[F_ROWS][F_COLS], int column)
{
    int i;

    for (i=F_ROWS-1; i>=0; i--) {
        if (field[i][column] != 0) {
            field[i][column] = 0;
        }
    }
}

/*0=no, 1=your_bot, 2=opponent, 3=stalemate */
int endgame(int f[F_ROWS][F_COLS], int player)
{
    int i, j;

    //check horizontals
    for(i=0; i<6; i++) {
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i][j+1]== player && f[i][j+2]== player && f[i][j+3]== player) {
                return player;
            }
        }
    }

    //check verticals
    for(i=0; i<=6-4; i++) {
        for(j=0; j<7; j++) {
            if(f[i][j]== player && f[i+1][j]== player && f[i+2][j]== player && f[i+3][j]== player ) {
                return player;
            }
        }
    }

    //check main diagonals (\)
    for(i=6-1; i>=4-1; i--) {
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i-1][j+1]== player && f[i-2][j+2]== player && f[i-3][j+3]== player) {
                return player;
            }
        }
    }

    //check other diagonals (/)
    for(i=0; i<=6-4; i++) {
        for(j=0; j<=7-4; j++) {
            if(f[i][j]== player && f[i+1][j+1]== player && f[i+2][j+2]== player && f[i+3][j+3]== player) {
                return player;
            }
        }
    }

    //check if stalement
    for(i=0; i<7; i++) {
        if(f[i][6-1]==0) {
            return 0;    //game haven't finished yet - there's at least one empty cell in a top of a row
        }
    }

    return 3; //stalemate - board is full
}

/* Calculates the score of a move */
int heuristic(int f[F_ROWS][F_COLS])
{
    int result = 0;
    int i, j;

    //check horizontals
    for(i=0; i<6; i++) {
        for(j=0; j<=7-4; j++) {
            if(f[i][j]!= 2 && f[i][j+1]!= 2 && f[i][j+2]!= 2 && f[i][j+3]!= 2) {
                result++;
            }
            if(f[i][j]!= 1 && f[i][j+1]!= 1 && f[i][j+2]!= 1 && f[i][j+3]!= 1) {
                result--;
            }
        }
    }

    //check verticals
    for(i=0; i<=6-4; i++) {
        for(j=0; j<7; j++) {
            if(f[i][j]!= 2 && f[i+1][j]!= 2 && f[i+2][j]!= 2 && f[i+3][j]!= 2 ) {
                result++;
            }
            if(f[i][j]!= 1 && f[i+1][j]!= 1 && f[i+2][j]!= 1 && f[i+3][j]!= 1 ) {
                result--;
            }
        }
    }

    return result;
}

int min()
{
}

int max()
{
}

int minimax(int board[F_ROWS][F_COLS], int depth, int turn /*1 or 2*/)
{

}
