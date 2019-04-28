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


	/****************************************** SOLUTION ******************************************/

		int start, move;
		int nopts[n+2];	
		int options[n+2][size+2];
		int i, candidate, solutions = 0;

		move = start = 0; 
		nopts[start]= 1;
		
		while (nopts[start] > 0)
		{
			if(nopts[move]>0) 
			{
				move++;
				nopts[move]=0;

				if(move==n+1)	//	SOLUTION FOUND!
				{
					solutions++;
					for(i=1;i<move;i++)
						printf("%2i\t",options[i][nopts[i]]);
					printf("\n");
				}
				else if(move == 1){
					for(candidate = size-1; candidate >=0; candidate --) 
					{
						nopts[move]++;
						options[move][nopts[move]] = candidate;
					}
				}
				else
				{
					for(candidate=1;candidate<=nopts[move-1];candidate++)
					{
						int topOfStack = options[move-1][nopts[move-1]];
						int x = topOfStack / n;
						int y = topOfStack % n;

						int current = options[move-1][candidate];
						int a = current / n;
						int b = current % n;
						int isValid = 1;

						//	Rook / Knight Move Checking
						if (!(a == x || b == y || (abs(x-a)==2 && abs(y-b)==1) || (abs(x-a)==1 && abs(y-b)==2))) {
							nopts[move]++;
							options[move][nopts[move]] = current; 
						}
					}
				}
			}
			else 
			{
				move--;
				nopts[move]--;
			}
		}

		printf(" No. of Solutions Found: %d\n", solutions);
	}

	printf("\n == PROGRAM END ==\n\n");
}
