#include <stdio.h>
#include <stdlib.h>

int main(){

	printf("\n == PROGRAM START ==\n");

	/* FILE READING */
	
	//	Variables
	FILE *fp;
	int numOfBoards, n;
	char c;

	fp = fopen("input.in", "r");
	fscanf(fp, "%d\n", &numOfBoards);
	printf("\n No. of Board(s): %d\n", numOfBoards);

	//	Process: Find All Solutions (per board)
	for(int i=0; i<numOfBoards; i++){

		printf("\n -- Board #%d --\n", i+1);
		fscanf(fp, "%d\n", &n);
		printf(" Matrix Size: %d\n", n);

		//	Matrix Creation
		int size = n*n;
		char *board = (char*) malloc(sizeof(char)*size);	
		for(int j=0; j<size; j++){
			fscanf(fp, "%c", &board[j]);
			if(j!=0 && (j+1)%n == 0) fscanf(fp, "\n");
		}


	/****************************************** Solution ******************************************/

		int start, move;
		int nopts[n+2];				//	top of stack
		int options[n+2][size+2];	//	matrix
		int i, candidate, solutions = 0;

		move = start = 0; 
		nopts[start]= 1;
		
		while (nopts[start] >0) //while dummy stack is not empty
		{
			if(nopts[move]>0) 
			{
				move++;
				nopts[move]=0; //initialize new move

				if(move==n+1) //solution found!
				{
					solutions++;
					// for(i=1;i<move;i++)
					// 	printf("%2i\t",options[i][nopts[i]]);
					// printf("\n");
				}
				else if(move == 1){
					for(candidate = size-1; candidate >=0; candidate --) 
					{
						nopts[move]++;
						options[move][nopts[move]] = candidate;
					}
				}
				else{

					for(candidate=1;candidate<=nopts[move-1];candidate++)
					{
						// get TOS, x position and y position
						int topOfStack = options[move-1][nopts[move-1]];
						int x = topOfStack / n;
						int y = topOfStack % n;
						// printf("Chancellor: %d\n", topOfStack);

						// Knight Moves Exclusion
						int knightMoves[8];
						int p,q;

							//	Up-Up-Left
							p = x-2; q = y-1;
							if (p < 0 || q < 0) knightMoves[0] = -1;
							else knightMoves[0] = (p*n)+q;

							//	Up-Up-Right
							p = x-2; q = y+1;
							if (p < 0 || q >= n) knightMoves[1] = -1;
							else knightMoves[1] = (p*n)+q;

							//	Up-Left-Left
							p = x-1; q = y-2;
							if (p < 0 || q < 0) knightMoves[2] = -1;
							else knightMoves[2] = (p*n)+q;

							//	Up-Right-Right
							p = x-1; q = y+2;
							if (p < 0 || q >= n) knightMoves[3] = -1;
							else knightMoves[3] = (p*n)+q;

							//	Down-Left-Left
							p = x+1; q = y-2;
							if (p >= n || q < 0) knightMoves[4] = -1;
							else knightMoves[4] = (p*n)+q;

							//	Down-Right-Right
							p = x+1; q = y+2;
							if (p >= n || q >= n) knightMoves[5] = -1;
							else knightMoves[5] = (p*n)+q;

							//	Down-Down-Left
							p = x+2; q = y-1;
							if (p >= n || q < 0) knightMoves[6] = -1;
							else knightMoves[6] = (p*n)+q;

							//	Down-Down-Right
							p = x+2; q = y+1;
							if (p >= n || q >= n) knightMoves[7] = -1;
							else knightMoves[7] = (p*n)+q;

						int current = options[move-1][candidate];
						int a = current / n;
						int b = current % n;
						int isValid = 1;

						// printf("\nasssessing...%d\n", current);
						for(int j = 0; j < 8; j++) {
							if(knightMoves[j] == current) {
								// printf("Conflict knight!\n");
								isValid = 0; break;
							}
						}

						// printf("%d==%d || %d==%d\n", a,x,b,y);
						if (a == x || b == y) {
							// printf("Conflict row/col!\n");
							isValid = 0;
						}

						if (isValid == 1) {
							nopts[move]++;
							options[move][nopts[move]] = current; 
							// printf("valid: %d ", current);
						}
					}
				// printf("\n");
				}
			}
			else 
			{
				// printf("backtracking...\n");
				move--;
				nopts[move]--;
			}
		}

		printf(" No. of Solutions Found: %d\n", solutions);
	}

	printf("\n == PROGRAM END ==\n\n");
}
