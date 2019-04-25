#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(int value, char *board, int *options, int *nopts, int move, int n) {

	char *fakeBoard = (char *) malloc(sizeof(char *)*(n*n));
	for (int i = 0; i < n*n; i++) {
		fakeBoard[i] = board[i];
	}

	printf("Value to check: %d\n", value);
	// Place All Chancellors
	for (int j = move-1; j > 0; j--) {

		int previousTOS = (options)[j][nopts[j]-1];
		fakeBoard[previousTOS] = 'C';
		
		printf("Plotting PreviousTOS: %d...\n", previousTOS);
	
		// Chancellor
		int x,y;
		x = previousTOS/n;
		y = previousTOS%n;

		//	Print: After Knighting
		printf("\n Before Knighting\n");
		for(int j=0; j<(n*n); j++){
			printf("%c", fakeBoard[j]);
			if(j!=0 && (j+1)%n == 0) printf("\n");
		}

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
		
		// Make All Valid Knight Moves Locked 
		for (int k=0; k<8; k++) {
			if (knightMoves[k] > 0 && knightMoves[k] < n*n)
				if (fakeBoard[knightMoves[k]] == '0')
					fakeBoard[knightMoves[k]] = 'x';
		}

		//	Print: After Knighting
		printf("\n After Knighting\n");
		for(int j=0; j<(n*n); j++){
			printf("%c", fakeBoard[j]);
			if(j!=0 && (j+1)%n == 0) printf("\n");
		}
		printf("\n");

		// -- Check In All Cells
		int a,b;
		for (int currentIndex=0; currentIndex<n*n; currentIndex++) {

			// Student
			a = currentIndex/n;
			b = currentIndex%n;

			if (previousTOS==currentIndex) continue;
			else if (fakeBoard[currentIndex] == 'C') continue;
			else if (fakeBoard[currentIndex] == 'x') continue;
			else if (x==a || y==b) fakeBoard[currentIndex] = 'x';

		}

		//	Print: After Knighting
		printf("\n RoW/CoL Update\n");
		for(int j=0; j<(n*n); j++){
			printf("%c", fakeBoard[j]);
			if(j!=0 && (j+1)%n == 0) printf("\n");
		}
		printf("\n");
	}

	if(fakeBoard[value]=='0') return 1;
	else return 0;
}

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

				if(move==n+1)
				{

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

					int *validMoves = (int *) malloc(sizeof(int)*(n*n)), count = 0;
					for (int i = n-1; i >= 0; i--) {
						if (isValid(i, board, *options, nopts, move, n) == 1) {
							printf("Found valid move at %d...\n", i);
							validMoves[count++] = i;
						}
					}					
					//---

					//	Push Candidates
					printf("Pushing [ ");
					for(int k = count-1; k >= 0; k--) {
						options[move][++nopts[move]] = validMoves[k];
						printf("%d ", validMoves[k]);
					} printf("]\n");

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