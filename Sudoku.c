#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*----- Global Declarations ----- */
int grid[9][9];

/*----- Function Declarations -----*/
void populateGrid(void);
void output(void);
int inputSudoku(char []);
int inputSudokuOtherVersion (char []);
void solveSudoku(void);
int getCandidates(int, int, int * );
void getCol(int, int *);
void getBox(int , int , int *);
int getNextBlank(int row,int col, int *nextPos);
void intro();
void menu();


int main(void){
	int input = 0;
	int error = 0;
	int i;
	char puzzleToSolve[20] = "Puzzle/Puzzle00";
	intro();
	menu();
	scanf("%i",&input);
 //--------- Need to move all of the code below to a new function and tidy up	
	switch (input) {
		case 1: strcpy(puzzleToSolve,"Puzzles/Puzzle001.txt");
			break;
		case 2: strcpy(puzzleToSolve,"Puzzles/Puzzle001.txt"); // Start with First puzzle
			break;
		case 3: printf("Running puzzle file from the website\n");
			inputSudokuOtherVersion("Puzzles/PuzzleList.txt");
			output();		
		case 4: return 0;
		
		default: 
			printf("Assume you only want Puzzle.txt solved.");
			break;		
		}
	
		for (i = 1;;i++){
			strcpy(puzzleToSolve,"Puzzles/Puzzle00");
				
			strcat(puzzleToSolve,".txt");
			error = inputSudoku("Puzzles//Puzzle001.txt");
			printf("\n\n");
			solveSudoku();
			getchar();
			if (error == 1) break;
			
		
		}
	    return 0;
}
/* ----- Populate the Sudoku Grid with Zero's ----- */
void populateGrid(void){
	int i=0,j=0;
	for (i=0;i<9;++i) { 
		for (j=0;j<9;++j) {
			grid[i][j]=0;
		}
	}
}
void output(){
	int i=0, j=0;
	for (i=0; i< 9 ;++i){
		printf("\n");
		if (i == 0 || i == 3 || i == 6 ){
			printf(" -------------------------------------------------  \n");
		}
		for (j=0;j < 9 ;++j){
			if (j==2 || j==5 || j==8) printf("  %d  |", grid[i][j]);		
			else if (j==0) printf(" | %d   ", grid[i][j]);
			else printf(" %d   ", grid[i][j]);			 
		}
	}
	printf("\n -------------------------------------------------  \n");
}
int inputSudoku(char puzzleToSolve []){
	int i = 0, j=0;
	FILE *puzzle = fopen(puzzleToSolve, "r");
	char str[9],eol;
	if (puzzle!=NULL) {
		for (i=0;i<9;++i){
			fscanf(puzzle,"%c%c%c%c%c%c%c%c%c%c", &str[0], &str[1], &str[2], &str[3], &str[4],&str[5],&str[6],&str[7],&str[8],&eol);
			for (j=0;j<9;++j){
				grid[i][j] = str[j] - 48; /* converts ascii to integer */
				str[j] = ' ';
			} 			
			if (feof (puzzle)){break;}
		}
		fclose(puzzle);
		return 0;
	}
	else {
		printf("No more puzzles to solve. Program will now exit.");			
		return 1;
	}
}
int inputSudokuOtherVersion(char puzzleFileToSolve []){
	
	int i = 0, j = 0,nbytes, bytes_read;
	size_t nnbytes;
	FILE *puzzle = fopen(puzzleFileToSolve, "r");
	int puzzlenumber = 1;
	char * puzzleTemp;
	printf("%s",puzzleFileToSolve);	
	if (puzzle!=NULL){
		//for (i = 0;i < puzzlenumber;i++){
			puzzleTemp = (char *) malloc (100 * sizeof(char) + 1);
			bytes_read = getline(&puzzleTemp,&nnbytes,puzzle);
			
		//}
		for (i = 0; i<9;i++){
			for (j=0;j<9;j++){
				if ((*(puzzleTemp + (i)*9 + j)) == '.'){
					grid[i][j] = 0;
				} 
				else grid[i][j] = (*(puzzleTemp + (i)*9 + j)) - 48;
			}

		}
		fclose(puzzle);
		return 0;
	}
	else printf("Error. Could not open puzzle");
	return 0;
}

	
	
int getCandidates(int row, int col, int* cands){
	int i = 0, j = 0, k = 0,array[9] = {0,0,0,0,0,0,0,0,0}, tempCol[9] = {0,0,0,0,0,0,0,0,0}, tempBox[9] = {0,0,0,0,0,0,0,0,0}, tempRow[9] = {0,0,0,0,0,0,0,0,0};
	memcpy(tempRow,grid[row],sizeof(tempRow));
	getCol(col, tempCol);
	getBox(row,col,tempBox);

	for (i=0;i<9;++i){
		if (tempRow[i] > 0){ array[tempRow[i] - 1] = tempRow[i];} 
		if (tempCol[i] > 0) {array[tempCol[i] - 1] = tempCol[i];}
		if (tempBox[i] > 0) {array[tempBox[i] - 1] = tempBox[i];}
		
	}

	for (i=0;i<9;++i){
		if (array[i] == 0){
		++j;
		cands[k] = i + 1;
		k++;	
		}			
	}
	if (j > 0) return j;
	else return 0;	
}				
void getCol(int numberOfCol, int *col){
	int i;
	for (i=0;i<9;++i){col[i] = grid[i][numberOfCol];}
	}
void getBox(int row, int col, int *tempBlock){
	int i,j;
	if (row<3){i=1;}
	else if (row <6 && row > 2){i=4;}
	else {i = 7;}
	if (col<3){j=1;}
	else if (col <6 && col > 2){j=4;}
	else {j = 7;}
	tempBlock[0] = grid[i-1][j-1];
	tempBlock[1] = grid[i][j-1];
	tempBlock[2] = grid[i+1][j-1];
	tempBlock[3] = grid[i-1][j];
	tempBlock[4] = grid[i][j];
	tempBlock[5] = grid[i+1][j];
	tempBlock[6] = grid[i-1][j+1];
	tempBlock[7] = grid[i][j+1];
	tempBlock[8] = grid[i+1][j+1];		
}
int bruteForce(int row,int col){
	// ----- Declarations -----
	int i=0, flag = 1, candFlag = 1,blankFlag = 1, nextPos[2] = {0,0};
	int cands[9] = {0,0,0,0,0,0,0,0,0};
	// ------------------------
	candFlag = getCandidates(row,col,cands); //get possible candidates for row and col.
	if (candFlag == 0){grid[row][col] = 0;return 0;} // checking if candidates is null. if null, return 0 (backtracking)
	blankFlag = getNextBlank(row,col,nextPos); //getting next square with a 0 (blank)
	if (blankFlag == 0){ // if no next blanks, set current box to the only candidate (as it can only be one), then return 1 (solved)
		grid[row][col] = cands[0];
		return 1;
	}
	for (i=0;i < 9;++i){
		
		grid[row][col] = cands[i];
		flag = bruteForce(nextPos[0],nextPos[1]);
		if (flag == 1){return 1;}
		if (cands[i + 1] == 0){grid[row][col] = 0;return 0;}
		}
		
	grid[row][col] = 0;
	return 0;
	}
int getNextBlank(int row,int col, int *nextPos){
	int i = row,j = col;
	
	while (i<9){
		while (j < 8){
			j++;
			if (grid[i][j] == 0){
				nextPos[0] = i;
				nextPos[1] = j; 
				return 1;
			}
			
				
		}
		i++; 
		j = -1;	
		}
	return 0;	
	}
void solveSudoku(){
	int solvedFlag = 0,firstPos[2] = {0,0};
	getNextBlank( 0 , -1 , firstPos);	
	solvedFlag = bruteForce(firstPos[0],firstPos[1]);
	
	if (solvedFlag ==1){
		printf("The solution: \n");
		output();
		printf("\n\nThe sudoku has been solved.");
	}
}
void intro(void){
	printf("*********************************************** \n");
	printf("    Welcome to Sudoku Solver Version 1.1.1 \n");
	printf("*********************************************** \n");	
	printf("Please have your puzzle file inside the same folder as the program.\n");
	
}
void menu(void) {
	printf(" ----- Menu -----\n");
	printf("1. Solve one puzzle (Puzzle.txt)\n");
	printf("2. Solve all puzzles in Puzzle folder\n");
	printf("3. Solve an entire puzzle file\n");
	printf("4. Exit\n");
	printf(" Your Choice : ");
}

	

	
	
	
	
	


	
	
