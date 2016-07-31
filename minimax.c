#include"minimax.h"

/* Random AI action for engine test */
void random_move(char *str1, char *str2, game_t *game)
{
    int col=0;

    /* action move */
    if (!strcmp(str1, "move")) {
        game->timebank = atoi(str2);
    }

    /* random move */
    col = rand() % F_COLS;
    fprintf(stdout, "place_disc %d\n", col);
}

/* Random AI action for engine test */
void ai_action(char *str1, char *str2, game_t *game)
{
    /* action move, get timebank */
    if (!strcmp(str1, "move")) {
        game->timebank = atoi(str2);
    }

    /* minimax decision for each move on the field*/
    int col, move;
    int n, val = -10000-1;

    for(col=0; col < 7; col++)
        if(game->field[6-1][col]==0) {
            put(game->field, col, 2);
            n = minimax(game->field, DEPTH, game->your_botid);
            if ( -n > val ) {
                val = -n;
                move = col;
            }
            rmv(game->field, col);
        }

    fprintf(stdout, "place_disc %d\n", move);
}

/* set disc */
int put(int field[F_ROWS][F_COLS], int column, int player)
{
    int i;

    for(i = 0; i < F_ROWS; i++) {
        if (field[i][column] == 0) {
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

/*returns:
  playernumber if player wins,
  0 if there is no winning move,
  3 if there is a stalemate*/
int check_game(int f[F_ROWS][F_COLS], int player)
{
    int i, j;

    //check horizontals
    for(i=0; i<F_ROWS; i++) {
        for(j=0; j<=F_COLS-4; j++) {
            if(f[i][j]==player && f[i][j+1]==player && f[i][j+2]==player && f[i][j+3]==player) {
                return player;
            }
        }
    }

    //check verticals
    for(i=0; i<=F_ROWS-4; i++) {
        for(j=0; j<F_COLS; j++) {
            if(f[i][j]==player && f[i+1][j]==player && f[i+2][j]==player && f[i+3][j]==player ) {
                return player;
            }
        }
    }

    //check main diagonals (\)
    for(i=F_ROWS-1; i>=4-1; i--) {
        for(j=0; j<=F_COLS-4; j++) {
            if(f[i][j]==player && f[i-1][j+1]==player && f[i-2][j+2]==player && f[i-3][j+3]==player) {
                return player;
            }
        }
    }

    //check other diagonals (/)
    for(i=0; i<=F_ROWS-4; i++) {
        for(j=0; j<=F_COLS-4; j++) {
            if(f[i][j]== player && f[i+1][j+1]==player && f[i+2][j+2]==player && f[i+3][j+3]==player) {
                return player;
            }
        }
    }

    //check if stalement
    for(i=0; i<F_COLS; i++) {
        if(f[i][F_ROWS-1]==0) {
            return 0; // At least one empty cell left
        }
    }

    return 3; //stalemate - field is full
}


int heuristic(int s[F_ROWS][F_COLS])
{
    int result = 0;
    int i, j;

    //check horizontals
    for(i=0; i<6; i++)
        for(j=0; j<=7-4; j++) {
            if(s[i][j]!= 2 && s[i][j+1]!= 2 && s[i][j+2]!= 2 && s[i][j+3]!= 2) {
                result++;
            }
            if(s[i][j]!= 1 && s[i][j+1]!= 1 && s[i][j+2]!= 1 && s[i][j+3]!= 1) {
                result--;
            }
        }

    //check verticals
    for(i=0; i<=6-4; i++)
        for(j=0; j<7; j++) {
            if(s[i][j]!= 2 && s[i+1][j]!= 2 && s[i+2][j]!= 2 && s[i+3][j]!= 2 ) {
                result++;
            }
            if(s[i][j]!= 1 && s[i+1][j]!= 1 && s[i+2][j]!= 1 && s[i+3][j]!= 1 ) {
                result--;
            }
        }

    return result;
}

int minimax(int field[F_ROWS][F_COLS], int depth, int turn /*1 or 2*/)
{
    int e;
    int col, best;
    int n;
    int player;

    if((e=check_game(field, player))) {
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
        if(turn==1) {
            return heuristic(field);
        } else {
            return -heuristic(field);
        }
    }

    best = -10000;

    for(col=0; col < 7; col++)     //check every move
        if(field[6-1][col]==0) {   //make sure column isn't empty
            put(field, col, turn);
            n = minimax(field, depth-1, 3-turn);
            if(turn==1) {
                if ( -n > best ) {
                    best = -n;
                }
            } else { //turn==2
                if ( -n > best ) {
                    best = -n;
                }
            }
            rmv(field, col);
        }

    return best;
}
