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

		printf("\n ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		printf(" /                                                            Board #%d                                                            /\n", i+1);
		printf(" ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		fscanf(fp, "%d\n", &n);
		printf("\n MATRIX SIZE: %d\n", n);

		//	Chancellors Creation
		char *chancellorStack = (char*) malloc(sizeof(char)*n);	
		int chancellorC = 0;
		
		//	Matrix Creation
		int size = n*n;
		char *board = (char*) malloc(sizeof(char)*size);	
		printf(" INITIAL BOARD CONFIGURATION \n ");
		for(int j=0; j<size; j++){
			fscanf(fp, "%c", &board[j]);
			printf("%c", board[j]);
			if(j!=0 && (j+1)%n == 0) {
				fscanf(fp, "\n");
				printf("\n ");
			}
			if (board[j] == 'C') chancellorStack[chancellorC++] = j;
		} printf("\n");

		//	Board Error!
		int hasNoSolution = 0, numberOfErrors = 0;
		for (int m=0; m<chancellorC; m++) {
			for (int k=m; k<chancellorC; k++) {
				if (m!=k)
				{
					int x = chancellorStack[m] / n;
					int y = chancellorStack[m] % n;
					int a = chancellorStack[k] / n;
					int b = chancellorStack[k] % n;
					if (a == x || b == y || (abs(x-a)==2 && abs(y-b)==1) || (abs(x-a)==1 && abs(y-b)==2)) {
						if (numberOfErrors==0) {
							printf("------------------------------------------------------------------------------------------------\n");
							printf(" There exist a chancellor(C) in the configuration that violates the rules for finding a solution!\n");							
							printf(" ------------------------------------------------------------------------------------------------\n");
							printf("\n **************************************************\n");
							printf(" * Please resolve conflict between the following: *\n *                                                *\n");
						}
						printf(" *  --> CHANCELLOR_A[%d][%d] & CHANCELLOR_B[%d][%d]   *\n", x,y,a,b);
						// printf(" *            xxxx   *\n");
						printf(" *            ");
						for (int p = 0; p < size; p++) {
							if (p%n==0 && p>=n) printf("                                *\n *            ");
							if (p==chancellorStack[m] || p==chancellorStack[k]) {
								printf("X");
							} else {
								printf("%c", board[p]);
							}
						}
						printf("                                *\n *                                                *\n");
						hasNoSolution = 1;
						numberOfErrors++;
					}
				}
			}
		}

	/****************************************** SOLUTION ******************************************/

		int solutions = 0;
		if (hasNoSolution==0)
		{
			int start, move;
			int nopts[n+2-chancellorC];	
			int options[n+2-chancellorC][size+2-chancellorC];
			int i, candidate;

			move = start = 0; 
			nopts[start] = 1;
			
			while (nopts[start] > 0)
			{
				if(nopts[move]>0) 
				{
					move++;
					nopts[move]=0;

					if(move==n+1-chancellorC)	//	SOLUTION FOUND!
					{
						printf(" Solution %d -- (\t", (solutions++)+1);
						
						int *solution = (int*) malloc(sizeof(int)*n);
						int count = 0;
						
						for (int i=0; i<chancellorC; i++){
							solution[count] = chancellorStack[i];
							count++;
							printf("%2i\t",chancellorStack[i]);
						}
						for(i=1;i<move;i++) {
							solution[count] = options[i][nopts[i]];
							count++;
							printf("%2i\t",options[i][nopts[i]]);							
						}
						printf(")\n");

						// -- Board Print
						for (int i = 0; i < size; i++)
						{
							int hasNoC = 1;
							for (int j = 0; j < count; j++)
							{
								if (i==solution[j]) {
									hasNoC = 0;
									break;
								}
							}

							if (i%n==0 && i>=n) printf("\n");
							if(hasNoC==1)
								printf("0");
							else
								printf("C");
							
						} printf("\n\n");

					}
					else if(move == 1){
						for(candidate = size-1; candidate >=0; candidate --) 
						{
							int x = candidate / n;
							int y = candidate % n;
							int isValid = 1;

							for (int i = 0; i < chancellorC; i++) {
								int a = chancellorStack[i] / n;
								int b = chancellorStack[i] % n;
								if (a == x || b == y || (abs(x-a)==2 && abs(y-b)==1) || (abs(x-a)==1 && abs(y-b)==2)) isValid = 0;
							}

							if (isValid==1) {
								nopts[move]++;
								options[move][nopts[move]] = candidate;							
							}
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
		}
		printf(" **************************************************\n\n");
		printf(" =========================\n");
		printf(" No. of Solutions Found: %d\n", solutions);
		printf(" Errors Found: %d\n", numberOfErrors);
	}

	printf("\n == PROGRAM END ==\n\n");
}