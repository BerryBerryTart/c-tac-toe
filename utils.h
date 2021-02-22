#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define WIDTH 3
#define HEIGHT 3
#define P1 'x'
#define P2 'o'

#ifndef _DRAWBOARD_
#define _DRAWBOARD_
void draw_board(char array[HEIGHT][WIDTH]){
    int i, j, floor;
    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            printf("%c", array[i][j]);
            if(j < WIDTH - 1){
                printf("|");
            }
        }
        printf("\n");
        if(i < HEIGHT - 1){
            for(floor = 0; floor < (HEIGHT * 2 - 1); floor++){
                printf("-");
            }
        }
        printf("\n");
    }
}
#endif

#ifndef _INITBOARD_
#define _INITBOARD_
void init_board(char array[HEIGHT][WIDTH]){
    int i, j;
    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            array[i][j] = ' ';
        }
    }
}
#endif

#ifndef _VALIDATE_
#define _VALIDATE_
bool validate(char space, int col, int row, bool player){
    if(col < 1 || col > 3 || row < 1 || row > 3 || space != ' '){
        return false;
    }
    return true;
}
#endif

#ifndef _WINCHECK_
#define _WINCHECK_
char winCheck(char array[HEIGHT][WIDTH], bool player){
    int i;
    char pChar;
    pChar = player ? 'x' : 'o';
    //horizontal check
    for (i = 0; i < WIDTH; i++){
        if(array[i][0] == pChar && array[i][1] == pChar && array[i][2] == pChar){
            return pChar;
        }
    }
    //vertical check
    for (i = 0; i < HEIGHT; i++){
        if(array[0][i] == pChar && array[1][i] == pChar && array[2][i] == pChar){
            return pChar;
        }
    }
    //diag check
    if(array[0][0] == pChar && array[1][1] == pChar && array[2][2] == pChar){
        return pChar;
    }
    else if (array[0][2] == pChar && array[1][1] == pChar && array[2][0] == pChar){
        return pChar;
    }

    return ' ';
}
#endif

#ifndef _TIECHECK_
#define _TIECHECK_
char tieCheck(char array[HEIGHT][WIDTH]){
    int i, j;

    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            if (array[i][j] == ' '){
                return ' ';
            }
        }
    }
    return 't';
}
#endif

#ifndef _MINIMAX_
#define _MINIMAX_
/*
-var isMaxing is true for bot and false for human
-return 10 for good for AI
-return -10 for good for HUMAN
*/
int minimax(char array[HEIGHT][WIDTH], int depth, bool isMaxing){
    char result = winCheck(array, isMaxing);
    if (result != ' '){
        return (result == 'o') ? 10 : -10;
    }
    result = tieCheck(array);
    if (result == 't'){
        return 0;
    }
    if (depth < 0){
        printf("MAX DEPTH REACHED OH NO!\n");
        exit(0);
        return -1;
    }
    //
    int i, j;
    //Evaluate bot move
    if (isMaxing){
        int bestScore = -32766, score;
        for (i = 0; i < HEIGHT; i++){
            for (j = 0; j < WIDTH; j++){
                if(validate(array[i][j], i + 1, j + 1, false)){
                    array[i][j] = 'o';
                    score = minimax(array, depth - 1, false);
                    array[i][j] = ' ';
                    if(score > bestScore){
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    else{
        int bestScore = 32766, score;
        for (i = 0; i < HEIGHT; i++){
            for (j = 0; j < WIDTH; j++){
                if(validate(array[i][j], i + 1, j + 1, true)){
                    array[i][j] = 'x';
                    score = minimax(array, depth - 1, true);
                    array[i][j] = ' ';
                    if(score < bestScore){
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    return 0;
}
#endif

#ifndef _GETNEXTMOVE_
#define _GETNEXTMOVE_
/*
Computer plays 'o'
*/
int * getNextMove(char array[HEIGHT][WIDTH], int moveCount){
    int i = 0, j = 0, bestScore = -32766, score = 0;
    static int botMove[2] = {-1, -1};
    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            if(validate(array[i][j], i + 1, j + 1, false)){
                array[i][j] = 'o';
                score = minimax(array, moveCount, false);
                array[i][j] = ' ';
                if(score > bestScore){
                    bestScore = score;
                    botMove[0] = i;
                    botMove[1] = j;
                }
            }
        }
    }
    return botMove;
}
#endif
