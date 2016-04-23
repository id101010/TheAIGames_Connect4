#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>:

// Defines
#define MAX_LENGTH      40
#define FIELD_WIDTH     3
#define FIELD_HEIGHT    3

// Globals
char input[MAX_LENGTH]; // Gets filled with stuff from stdin

typedef struct gamesettings_s{  // Game object struct for settings, actions and updates
    // Startup stuff
    int timebank;
    int time_per_move;
    char *player_names;
    int your_botid;
    int field_columns;
    int field_rows;
 
    // Update stuff
    int round;
    char board [FIELD_WIDTH][FIELD_HEIGHT] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };
    
    // Action stuff
    int move;
    int pace_disc;
}gamesettings_t

// Abort on failure
void die(const char *message)
{
    if(errno){
        perror(message);
    }else{
        printf("[ERROR] %s\n ", message);
    }

    exit(EXIT_FAILURE);
}

// Read line from stdin (safe)
char *get_line(char *s, size_t n, FILE *f)
{
    char *p = fgets(s, n, f);

    if(p != NULL){
        strtok(s, "\n");
    }

    if(s[0] == '\n'){
        s[0] = 0;
    }

    return p;
}

// Parse arguments from game engine
void parser(void)
{
    if(get_line(input, MAX_LENGTH, stdin) != NULL){
        if(!strstr(input, "settings")){
            // Handle settings string
        }
        if(!strstr(input, "action")){
            // Handle action string
        }
        if(!strstr(input, "update")){
            // Handle update string
        }
    }
}

// Main routine
int main(int argc, char **argv)
{
    // Do someting
    exit(EXIT_SUCCESS);
}
