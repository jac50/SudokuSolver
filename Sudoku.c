#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/*----- Global Declarations ----- */
int tempGrid[9][9];
int grid[9][9];
char flag,flag2;
/*----- Function Declarations -----*/
void populateGrid(void);
void output(void);
int compare(const int * a,const int * b);
char check9(int []);
void inputSudoku(void);
void getRow(int , int *);
void getCol(int, int *);
void getBox(int , int , int *);
void solveSudoku(void);
int getCandidates(int, int, int * );
// char gridCheck(void);
int bruteForce(int ,int );
int getNextBlank(int row,int col, int *nextPos);
void setTempGrid();
void intro();
/* ----- Start of Main ----- */
int main(void){
    int flag;
    intro();
    inputSudoku();
    setTempGrid();

    printf("\n\n\n\n");
    solveSudoku();
    // if (gridCheck() == 'T'){printf("\n Puzzle has been solved.");}
    getchar();
    return 0;
}
void populateGrid(void){
/* ----- Populate the Sudoku Grid with Zero's ----- */
int i=0,j=0;
		 for (i=0;i < 9;++i); { 
			 for (j=0;j < 9;++j) {
				 grid[i][j]=0;
			 }
		 }
	 }
void output(){
	int i=0, j=0;
		 for (i=0; i< 9 ;++i){
			printf("\n");
			if (i == 0 || i == 3 || i == 6 ){
				printf("  --------------------------------------------------  \n");
			}
			for (j=0;j < 9 ;++j){
				if (j==2 || j==5 || j==8) printf("  %d  |", tempGrid[i][j]);		
				else printf("  %d   ", tempGrid[i][j]);
				 
			}
		}
	}
int compare(const int * a,const int * b){
  if (*a==*b)
    return 0;
  else
    if (*a < *b)
        return -1;
     else
      return 1;
}

/* char check9(int array[]){
int i;
	----- Declarations ----- 
	qsort(array, 9, sizeof(int),compare);  /* find out why compare wont work 
	for (i=0;i<9;++i){
			 if((array[i] != i+1))
				{return 'F';}
			 }
	return 'T';
}  */ 

/* char gridCheck(void){
	 char flagRow = 'T',flagCol = 'T', flagBlock = 'T';
	 int i = 0, j=0,k=0,count = 0;  //Declaring Counters (i for row, j for column)
	 int tempRow[9], tempCol[9], tempBlock[9]; //Temporary Variables for Row and Columns
	 for (i = 0;i<9;++i)
	 {
		for (j=0;j<9;++j)
		{
			tempRow[j] = tempGrid[i][j]; //Saves all elements in row i to tempRow
			tempCol[j] = tempGrid[j][i];//Saves all elements in column i to tempCol
		}
		//
		flagRow = check9(tempRow);
		flagCol = check9(tempCol);
		if (flagRow == 'F' || flagCol == 'F')
		{return 'F'; }
		//
	}
	//----- Checking the Block -----
	for (i=1;i<9;i+=3)
	{
		for(j=1;j<9;j+=3)
		{
			tempBlock[0] = tempGrid[i-1][j-1];
			tempBlock[1] = tempGrid[i][j-1];
			tempBlock[2] = tempGrid[i+1][j-1];
			tempBlock[3] = tempGrid[i-1][j];
			tempBlock[4] = tempGrid[i][j];
			tempBlock[5] = tempGrid[i+1][j];
			tempBlock[6] = tempGrid[i-1][j+1];
			tempBlock[7] = tempGrid[i][j+1];
			tempBlock[8] = tempGrid[i+1][j+1];
			
			flagBlock = check9(tempBlock);
			if (check9(tempBlock) == 'F')
			{
				return 'F';
			}	
		}
	}
	return 'T';
}
*/ 
void inputSudoku(void){
	int temp[9] = {0,0,0,0,0,0,0,0,0}, i = 0, j=0;
	FILE *puzzle = fopen("Puzzle.txt", "r");
	char str[9],eol;
	if (puzzle!=NULL)
	{
		for (i=0;i<9;++i){
			fscanf(puzzle,"%c%c%c%c%c%c%c%c%c%c", &str[0], &str[1], &str[2], &str[3], &str[4],&str[5],&str[6],&str[7],&str[8],&eol);
			for (j=0;j<9;++j){
				grid[i][j] = str[j] - 48; /* converts ascii to integer */
				str[j] = ' ';
			} /* converts ascii to integer */
			
			if (feof (puzzle)){break;}
		}
		fclose(puzzle);
	}
	else {perror("Puzzle.txt");}
				
}
int getCandidates(int row, int col, int* cands){
	int temp[9];
	int i = 0, j = 0, k = 0,array[9] = {0,0,0,0,0,0,0,0,0}, tempCol[9] = {0,0,0,0,0,0,0,0,0}, tempBox[9] = {0,0,0,0,0,0,0,0,0}, tempRow[9] = {0,0,0,0,0,0,0,0,0};
	memcpy(tempRow,tempGrid[row],sizeof(tempRow));
	// getRow(row, tempRow);
	// memcpy(tempCol,tempGrid[][col],sizeof(tempCol);
	getCol(col, tempCol);
	getBox(row,col,tempBox);

	for (i=0;i<9;++i){
		if (tempRow[i] > 0){ array[tempRow[i] - 1] = tempRow[i];} 
		if (tempCol[i] > 0) {array[tempCol[i] - 1] = tempCol[i];}
		if (tempBox[i] > 0) {array[tempBox[i] - 1] = tempBox[i];}
		
	}
	
	//printf("\n %i %i %i %i %i %i %i %i %i\n",array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8]);
	
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
	int i,j;
	for (i=0;i<9;++i){col[i] = tempGrid[i][numberOfCol];}
	}
void getBox(int row, int col, int *tempBlock){
	int r,c,i,j;
	if (row<3){i=1;}
	else if (row <6 && row > 2){i=4;}
	else {i = 7;}
	if (col<3){j=1;}
	else if (col <6 && col > 2){j=4;}
	else {j = 7;}
			tempBlock[0] = tempGrid[i-1][j-1];
			tempBlock[1] = tempGrid[i][j-1];
			tempBlock[2] = tempGrid[i+1][j-1];
			tempBlock[3] = tempGrid[i-1][j];
			tempBlock[4] = tempGrid[i][j];
			tempBlock[5] = tempGrid[i+1][j];
			tempBlock[6] = tempGrid[i-1][j+1];
			tempBlock[7] = tempGrid[i][j+1];
			tempBlock[8] = tempGrid[i+1][j+1];	
	
	}
void getRow(int row, int *tempRow){
int i;
for (i=0;i<9;++i) tempRow[i] = tempGrid[row][i];
}
	/* Implement...

	*/
int bruteForce(int row,int col){
	// ----- Declarations -----
	int i=0, flag = 1, candFlag = 1,blankFlag = 1, nextPos[2] = {0,0};
	int cands[9] = {0,0,0,0,0,0,0,0,0};
	// ------------------------
	candFlag = getCandidates(row,col,cands); //get possible candidates for row and col.
	if (candFlag == 0){tempGrid[row][col] = 0;return 0;} // checking if candidates is null. if null, return 0 (backtracking)
	blankFlag = getNextBlank(row,col,nextPos); //getting next square with a 0 (blank)
	if (blankFlag == 0){ // if no next blanks, set current box to the only candidate (as it can only be one), then return 1 (solved)
		tempGrid[row][col] = cands[0];
		return 1;
	}
	for (i=0;i < 9;++i){
		
		tempGrid[row][col] = cands[i];
		flag = bruteForce(nextPos[0],nextPos[1]);
		if (flag == 1){return 1;}
		if (cands[i + 1] == 0){tempGrid[row][col] = 0;return 0;}
		}
		
	tempGrid[row][col] = 0;
	return 0;
	}
int getNextBlank(int row,int col, int *nextPos){
	int i = row,j = col;
	
	while (i<9){
		while (j < 8){
			j++;
			if (tempGrid[i][j] == 0){
				nextPos[0] = i;
				nextPos[1] = j; 
				return 1;
			}
			
				
		}
		i++; j = -1;	
		}
	return 0;	
	}
void solveSudoku(){
	int firstRow = 0,firstCol = 0,solvedFlag = 0,firstPos[2] = {0,0};
	setTempGrid();
	getNextBlank( 0 , -1 , firstPos);
	
	solvedFlag = bruteForce(firstPos[0],firstPos[1]);
	
	if (solvedFlag ==1){
		output();
		printf("\n\nThe sudoku has been solved.");
	}
}
void setTempGrid(){
	memcpy(tempGrid,grid,sizeof(tempGrid));
		}
void intro(void){
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("Welcome to Sudoku Solver Version One\n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("Please have your puzzle file inside the same folder as the program. Many Thanks\n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	printf("******************************************* \n");
	}
	
	
	
	
	


	
	
