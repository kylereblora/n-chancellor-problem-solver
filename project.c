#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct configuration {
	char configS[256];
	struct configuration *next;
} config;

int main()
{
	
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

		//	Print: Initial Configuration
		printf("\n Initial Configuration\n");
		for(int j=0; j<(n*n); j++){
			printf("%c", board[j]);
			if(j!=0 && (j+1)%n == 0) printf("\n");
		}
		printf("\n");

		/****************************************** Solution ******************************************/

		int start, move;
		int nopts[n+2];				//	top of stack
		int options[n+2][size+2];	//	matrix
		int i, candidate;

		move = start = 0;
		nopts[start] = 1;

		while (nopts[start] > 0)
		{
			if(nopts[move]>0)
			{
				move++;
				nopts[move]=0;

				if(move==n-1)
				{
					printf("Solution\n");

				}

				//	Insert All Candidates
				else if (move == 1)
				{
					for(candidate = size-1; candidate>=0; candidate--)
					{
						nopts[move]++;
						options[move][nopts[move]] = candidate;
					}
				}

				//	Valid Moves
				else
				{

					int previousTOS = options[move-1][nopts[move-1]];
					int *validMoves = (int *) malloc(sizeof(int)*(n*n)), count = 0;
					char *fakeBoard = (char *) malloc(sizeof(char *)*(n*n));
					for (int i = 0; i < n*n; i++) {
						fakeBoard[i] = board[i];
					}
					
					fakeBoard[previousTOS] = 'C';

					// Chancellor
					int x,y;
					x = previousTOS/n;
					y = previousTOS%n;

					// Knight Moves Exclusion
					int knightMoves[8];
					if (x+2<=n && y+1 <=n) knightMoves[0] = ((x+2)*n)+(y+1);
					else knightMoves[0] = -1;
					if (x+2<=n && y-1 >=0) knightMoves[1] = ((x+2)*n)+(y-1);
					else knightMoves[1] = -1;
					if (x-2>=0 && y+1 <=n) knightMoves[2] = ((x-2)*n)+(y+1);
					else knightMoves[2] = -1;
					if (x-2>=0 && y-1 >=0) knightMoves[3] = ((x-2)*n)+(y-1);
					else knightMoves[3] = -1;
					if (x+1<=n && y+2 <=n) knightMoves[4] = ((x+1)*n)+(y+2);
					else knightMoves[4] = -1;
					if (x+1<=n && y-2 >=0) knightMoves[5] = ((x+1)*n)+(y-2);
					else knightMoves[5] = -1;
					if (x-1>=0 && y+2 <=n) knightMoves[6] = ((x-1)*n)+(y+2);
					else knightMoves[6] = -1;
					if (x-1>=0 && y-2 >=0) knightMoves[7] = ((x-1)*n)+(y-2);
					else knightMoves[7] = -1;
					
					for (int j=0; j<8; j++) {
						if (knightMoves[j] > 0 && knightMoves[j] < n*n)
							if (fakeBoard[knightMoves[j]] == '0')
								fakeBoard[knightMoves[j]] = 'x';
					}

					// -- check per cell
					int a,b;
					for (int currentIndex=0; currentIndex<n*n; currentIndex++) {

						// Student
						a = currentIndex/n;
						b = currentIndex%n;

						if (previousTOS==currentIndex) continue;
						else if (fakeBoard[currentIndex] == 'C') continue;
						else if (fakeBoard[currentIndex] == 'x') continue;
						else if (x==a || y==b) fakeBoard[currentIndex] = 'x';
						else validMoves[count++] = currentIndex;

					}

					//	Push Candidates
					for(int k = count-1; k >= 0; k--) {
						options[move][++nopts[move]] = validMoves[k];
					}

				}
			}
			else 
			{
				move--;
				nopts[move]--;

			}
		}
	}
	fclose(fp);
	return 0;
}