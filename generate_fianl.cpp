#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 10
#define COLS 10
#define N 20			// number of cols
#define M 11			// number of rows
#define _2COLS 20
#define DIRECTION_NUM 4
#define DIRECTION_EAST 2
#define DIRECTION_SOUTH 3
#define DIRECTION_WEST 4
#define DIRECTION_NORTH 1
#define true 1
#define false 0

int CellStatus[ROWS*COLS];

bool is_Connect(const int* CellStatus, int c1, int c2)
{
	while(CellStatus[c1] >= 0) c1 = CellStatus[c1];
	while(CellStatus[c2] >= 0) c2 = CellStatus[c2];
	if(c1 == c2) 
		return true;
	else 
		return false;
}

bool all_Connect(const int * CellStatus)
{
	int i, count_root = 0;
	for(i = 0; i < ROWS*COLS; i++)
	{
		if(CellStatus[i] < 0) count_root++;
	}
	if(1 == count_root) 
		return true;
	else 
		return false;
}

void union_Cells(int *CellStatus, int c1, int c2)
{
	while(CellStatus[c1] >= 0) c1 = CellStatus[c1];
	while(CellStatus[c2] >= 0) c2 = CellStatus[c2];
	
	// the depth of the tree with c2 is deepper than Tc1, Tc1 attach to Tc2
	if(CellStatus[c1] > CellStatus[c2])
	{
		CellStatus[c1] = c2;        
	}
	else
	{
		if(CellStatus[c1] == CellStatus[c2]) CellStatus[c1]--;
		CellStatus[c2] = c1;
	}
}

int main(int argc, char* argv[])
{
	for(int i = 0;i<ROWS*COLS;++i)
	{
		CellStatus[i] = -1;
	}
	int c1;		//Start from Cell_1
	int c2;
	int direction;		//Direction to dig
	int old_direction;
    //int CELL_NUM = ROWS*COLS;
 	int row;
	int col;
	
	static char c_maze[M][N + 1];
    static int maze[M][N + 1] = {0};
  	
	//Above are announcements
  	
  	for(row = 0;row < M; ++row)
	{
		for(col = 0; col < N + 1; ++col)
		{
			if(maze[row][col] == 0 && col% 2 != 0)
			{
				c_maze[row][col] = *"_";}
				else c_maze[row][col] = *"|";
			
		}
	}
    
    //Above is to in itialize the maze
    
    srand((unsigned)time(NULL));		//Generate the seed for rand()
	
	while(1)
	{
		int CELL_NUM = COLS*ROWS;
		c1 = rand()%CELL_NUM;
        direction = rand()%(4)+1;
		switch(direction)
		{
			case DIRECTION_EAST:
				if(c1%COLS == COLS-1) c2 = -1;
				//else if(old_direction == DIRECTION_WEST) c2 = -1;
				else c2 = c1 + 1;
				break;
			case DIRECTION_SOUTH:
				if((ROWS-1) == (c1 - c1%COLS)/COLS) c2 = -1;
				//else if(old_direction == DIRECTION_NORTH) c2 = -1;
				else c2 = c1 + COLS;
				break;
			case DIRECTION_WEST:
				if(c1%COLS == 1) c2 = -1;
				//else if(old_direction == DIRECTION_EAST) c2 = -1;
				else c2 = c1 - 1;
				break;
			case DIRECTION_NORTH:
				if(0 == (c1 - c1%COLS)/COLS) c2 = -1;
				//else if(old_direction == DIRECTION_SOUTH) c2 = -1;
				else c2 = c1 - COLS;
				break;
			default:
				exit(0);
				break;
		}
			
		if(c2 < 0) continue;
		// judge whether the two adjacent rooms chose by random are connected
		if(is_Connect(CellStatus, c1, c2)) continue;
		/*else
		{
			old_direction = direction;	
			CellStatus[c1] = 1;
			CellStatus[c2] = 1;		//Mark the current 2 cells to walked
			maze[((c1-c1%COLS)/COLS)+1][((c1%COLS)*2)+1] = direction;				
			c1 = c2;		//Step forward
		}*/
		// If start and end point connects, the maze is created successfully
		else
		{
			union_Cells(CellStatus, c1, c2);
			maze[(c1-c1%COLS)/COLS][c1%COLS]=direction;
			maze[(c2-c2%COLS)/COLS][c2%COLS]=(direction+2)%4;
		}
		if(is_Connect(CellStatus, 0, 99)) break;
		//if(CellStatus[1] == CellStatus[99])
		//break;
	} 
   
	
	
	/*for(row = 1; row < M - 1; ++row)
	{
	for(col = 1; col <N - 1; ++col)
		{
		if(maze[row][col] == 0 && col%2 != 0){
			maze[row][col] = rand()%(4)+1;}
		if(maze[row][col] == 4 && col == 1){
			maze[row][col] = 2;}
		if(maze[row][col] == 1 && row == 1){
			maze[row][col] = 3;}
		}
	}*/
	
	//Above is to random the rest of the cells
	
	for(row = 0; row <M; ++row)
	{
	for(col = 0; col <N + 1; ++col){
			printf("%d ", maze [row][col]);
			}
		printf("\n");
	}
	
	//Above is to print the integer array	
		
	for(row = 0;row < M; ++row)
	{
		for(col = 1; col < N + 1; col = col + 2)
		{

			if(maze[row][col] == 1)
			{
				c_maze[row - 1][col] = *" ";}
			if(maze[row][col] == 2)
			{
				c_maze[row][col + 1] = *" ";}
			if(maze[row][col] == 3)
			{
				c_maze[row][col] = *" ";}
			if(maze[row][col] == 4)
			{
				c_maze[row][col - 1] = *" ";}
		}
	}
	
	c_maze[1][0] = ' ';
	c_maze[10][20]  = ' ';
	
	for(row = 0; row <M; ++row)
	{
		for(col = 0; col <N + 1; ++col){
			printf("%c", c_maze [row][col]);
			}
		printf("\n");
	}
	return 0;	
}
