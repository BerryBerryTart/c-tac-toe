#include <stdio.h>
#include "utils.h"

int sum(int n){
	if (n == 0){
		return n;
	}
	else{
		return sum(n - 1);
	}
}

int main(){
	// int * botMove;
	// char board[WIDTH][HEIGHT] =	{
	// 	'o','x','o',
	// 	'x','x','o',
	// 	'x',' ',' '
	// };
	// botMove = getNextMove(board, 9);
	// printf("%d, %d\n", botMove[0], botMove[1]);
	int res = sum(10);

	printf("%d\n", res);

    return 0;
}
