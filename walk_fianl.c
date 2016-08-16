#include <stdio.h>
#include <stdlib.h>
#define N 10
#define DIRECTION_EAST 1
#define DIRECTION_SOUTH 2
#define DIRECTION_WEST 3
#define DIRECTION_NORTH 0
#define true 1
#define false 0



int maze[10][10] = {        
    {1,1,1,1,1,1,1,1,1,1},  
    {1,0,0,1,1,0,0,1,0,1},  
    {1,0,0,1,0,0,0,1,0,1},  
    {1,0,0,0,0,1,1,0,0,1},  
    {1,0,1,1,1,0,0,0,0,1},  
    {1,0,1,0,1,0,0,0,0,1},  
    {1,0,1,0,0,0,1,0,0,1},  
    {1,0,0,1,1,0,1,1,0,1},  
    {1,1,0,0,0,0,0,0,0,1},  
    {1,1,1,1,1,1,1,1,1,1}}; 	//定义一个数组，0表示通道，1表示墙
    
    
int walked[10][10] = {        
    {1,1,1,1,1,1,1,1,1,1},  
    {1,0,0,1,1,0,0,1,0,1},  
    {1,0,0,1,0,0,0,1,0,1},  
    {1,0,0,0,0,1,1,0,0,1},  
    {1,0,1,1,1,0,0,0,0,1},  
    {1,0,1,0,1,0,0,0,0,1},  
    {1,0,1,0,0,0,1,0,0,1},  
    {1,0,0,1,1,0,1,1,0,1},  
    {1,1,0,0,0,0,0,0,0,1},  
    {1,1,1,1,1,1,1,1,1,1}};	//定义一个数组，表示已经走过的单元
    
    
char step[50] = {-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1,-1,-1,-1,-1,
				-1,-1};		//定义一个一维数组，表示走过的路径


int main()
{
	int row;
	int col;
	int i = -2;
	
	maze[1][1] = -1;	//Start from here
	
	for(row = 0; row < N; ++row)
	{	
		for(col = 0; col < N; ++col)
		{
			printf("%d ", maze[row][col]);
		}
		printf("\n");
	}		
	
	int j = 0;	//Counter for step
	int s;
	int direction = 0;
	int change = false;		//If there is a aviliable step
	int ward;	//Direction
	int canBack = 0;	//If it can go back
	
	row = 1;
	col = 1;
	
	while(1)
	{	
		switch(direction)
		{
			case DIRECTION_NORTH:
				if(maze[row - 1][col] == 0)
				{
					maze[row - 1][col] = -1;
					row = row -1;
					change = true;
					walked[row - 1][col] = 1;
					step[j] = direction;
					++j;
				}
				else ++direction;
				break;
			
			case DIRECTION_EAST:
				if(maze[row][col + 1] == 0)
				{
					maze[row][col + 1] = -1;
					col = col +1;
					change = true;
					walked[row][col + 1] = 1;
					step[j] = direction;
					++j;
				}				
				else ++direction;
				break;
		
			case DIRECTION_SOUTH:
				if(maze[row + 1][col] == 0)
				{
					maze[row + 1][col] = -1;
					row = row + 1;
					change = true;
					walked[row + 1][col] = 1;
					step[j] = direction;
					++j;
				}				
				else ++direction;
				break;
			
			case DIRECTION_WEST:
				if(maze[row][col - 1] == 0)
				{
					maze[row][col - 1] = -1;
					col = col - 1;
					change = true;
					walked[row][col - 1] = 1;
					step[j] = direction;
					++j;
				}				
				else ++direction;
				break;
				
		}
		
		//printf("j = %d\t",j);
		
		
		if(change)
		{
			change = false;
			direction = 0;
		}
		
		if(direction == 4)
		{
			s = j;	
			
			while(1)
			{
				//printf(" step[%d] = %d ", s, step[s] );
				switch(step[s])
				{
					case DIRECTION_NORTH:
						maze[row][col] = i;
						row = row + 1;
						break;
					
					case DIRECTION_EAST:
						maze[row][col] = i;
						col = col -1;
						break;
					
					case DIRECTION_SOUTH:
						maze[row][col] = i;
						row = row - 1;
						break;
					
					case DIRECTION_WEST:
						maze[row][col] = i;
						col = col + 1;
						break;
				}
			
			
			
				for(ward = 0;ward < 4;++ward)
				{
					switch(ward)
					{
						case DIRECTION_NORTH:
							if(maze[row - 1][col] == 0 && walked[row - 1][col] != 1)
							{
								direction = DIRECTION_NORTH;
								canBack = true;
							}
							else
							break;
						
						case DIRECTION_EAST:
							if(maze[row][col + 1] == 0 && walked[row][col + 1] != 1)
							{
								direction = DIRECTION_EAST;
								canBack = true;
							}
							else
							break;
						
						case DIRECTION_SOUTH:
							if(maze[row + 1][col] == 0 && walked[row + 1][col] != 1)
							{
								direction = DIRECTION_SOUTH;
								canBack = true;
							}
							else
							break;
						
						case DIRECTION_WEST:
							if(maze[row][col - 1] == 0 && walked[row][col - 1] != 1)
							{
								direction = DIRECTION_WEST;
								canBack = true;
							}
							else
							break;
					}
				
					if(canBack)
					break;
				
			}//for的括号
		if(canBack == 0){
		s = s - 1;}
		
		if(canBack){
		canBack = 0;
		break;}
		}//while的括号
		
		--i;//Change the right route number
	
	}//if(direction == 4)的括号 
		
	if(row == 8 && col == 8)	//End here
	break;
		
	}
	
	maze[1][0] = -1;
	maze[8][9] = -1;


	printf("\n");
	for(row = 0; row < N; ++row)
	{	
		for(col = 0; col < N; ++col)
		{
			printf("%d\t", maze[row][col]);
		}
		printf("\n");
	}
	
	for(row = 0; row < N; ++row)
	{	
		for(col = 0; col < N; ++col)
		{
			if(maze[row][col] == 1)
			{
				printf("▇");
			}
			
			if(maze[row][col] == 0)
			{
				printf("  ");
			}
			
			if(maze[row][col] == -1)
			{
				printf("●");
			}
			
			if(maze[row][col] < -1)
			{
				printf("  ");
			}
		}
		printf("\n");
	}					
}
