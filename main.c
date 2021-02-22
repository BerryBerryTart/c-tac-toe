#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

int main(){
    int moveCol = 0, moveRow = 0, i, turnNum = 9;
    int * botMove;
    bool player = true, valid = false;
    char win = ' ', tie = ' ';
	char board[WIDTH][HEIGHT];
    init_board(board);

    //Game loop
    for(i = 0; i < (WIDTH * HEIGHT); i++){
        if (player == true){
            printf("PLAYER ONE GO (%c)\n", P1);
        }
        else{
            printf("PLAYER TWO GO (%c)\n", P2);
        }
        //Validation loop
        if(player){
            while(!valid){
                printf("Col: ");
                fscanf(stdin, "%d", &moveCol);
                printf("Row: ");
                fscanf(stdin, "%d", &moveRow);
                valid = validate(board[moveRow - 1][moveCol - 1], moveCol, moveRow, player);
            }
        }
        //bot move
        if(!player){
            botMove = getNextMove(board, turnNum);
            if(botMove[0] == -1){
                printf("ERROR!!!!\n");
                break;
            }
            else{
                moveRow = botMove[0] + 1;
                moveCol = botMove[1] + 1;
                printf("Computer: Col: %d, Row: %d\n", moveCol, moveRow);
            }
        }
        //Player makes da move
        board[moveRow - 1][moveCol - 1] = player ? P1 : P2;
        draw_board(board);
        win = winCheck(board, player);
        if(win != ' '){
            int winner = player ? 1 : 2;
            printf("Player %d Won!\n", winner);
            break;
        }
        if(tieCheck(board) != ' '){
            printf("Tie!\n");
        }
        player = !player;
        valid = false;
        turnNum--;
    }
    return 0;
}
