// ConsoleApplication8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream> 
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;


int  centre, score;
char s, world[height][length];
const interval = 200; height = 30; length = 40;
int distance = 0, falltime = 0, x = 0, y = 0, tuk = 0 falltime = 0;

void changepos();
void make_an_obstacle();
void make_world();
void show_world();
void checkscore();
bool gameover();

int main()  //function for playing game
{
	srand(time(0));
	int i, j;
	char s;
	for (j = 0; j<height+1; j++)  //setting screen
	{
		for (i = 0; i<length; i++)
		{
			if (j<height) world[i][j] = ' ';
			if (y == height) world[i][j] = '#';
		}
	}
	world[10][10] = '@'; 
	screen();      
	while (1)
	{
		s = '~';  
		Sleep(interval);  
		t++;              
		if (_kbhit()) 
		{
			s = _getch();        
			if (s != '~') tuk = 1; 
		}
		for (i = 0; i<length; i++) world[i][height] = '#';
		changepos();                       
		checkscore();                 
		if (gameover() == true)
		{
			system("pause");
			return 0;   
		}
		make_world();                             
		show_world();                            
        
		if (tuk>0) tuk++;           
		if (tuk == 3) tuk = 0;          
	}	
}

void changepos() 
{
	int i, j;
	if (tuk>0) 
	{
		falltime = 0;
		for (j = 0; j<height; j++)   
		{
			for (i = 0; i<length; i++)
			{
				if (world[i][j] == '@')
				{
					if (j>0)
					{
						world[i][j - 1] = '@';  
						world[i][j] = ' ';
						x = i;        
						y = j;      
						return;        
					}
				}
			}
		}
	}
	else   
	{
		falltime++;
		for (j = 0; j<height; j++)
		{
			for (i = 0; i<length; i++)
			{
				if (world[i][j] == '@')
				{
					if (j<length)  
					{
						if (falltime<3)   
						{
							world[i][j + 1] = '@';
							world[i][j] = ' ';
							x = i;
							y = j + 1;
							return;
						}
						else if (falltime>2 && falltime<5)  
						{
							world[i][j + 2] = '@';
							world[i][j] = ' ';
							x = i;
							y = j + 2;
							return;
						}
						else if (falltime>4)
						{
							world[i][j + 3] = '@';
							world[i][j] = ' ';
							x = i;
							y = j + 3;
							return;
						}
					}
					else
					{
						return;  
					}
				}
			}
		}
	}
}
void make_an_obstacle()
{
	centre = (rand() % 11) + 5; 
	for (j = 0; j<height; j++)  world[length][j] = '#';  	
	world[length][centre - 1] = ' '; 
	world[length][centre] = ' ';
	world[length][centre + 1] = ' ';	
	distance = 0;
}

void make_world()
{
	if (distance == 10) make_an_obstacle();
	for (int j = 0; j <= height, j++)
	{
		for (int i = 0; i<= length, i++)
		{ 
			if (world[i][j] == '#')
			{
				if (i > 0)
				{
					world[i - 1][j] = '#';
					world[i][j] = ' ';
				}
				if (i == 0) world[i][j] = ' ';
			}
		}
	}
}


void show_world()
{
	int i, j;
	system("cls");    
	for (j = 0; j<height+1; j++) 
	{
		for (i = 0; i<length; i++)
		{
			if (i<length-1) cout << world[i][j];
			if (i ==length-1) cout << world[i][j] << endl;
		}
	}
	cout << "" << endl;
	cout << "Your Score: " << score;
}

void checkscore()  
{
	int j;
	for (j = 0; j<height; y++)
	{
		if (world[x][j] == '#')  
		{
			score++;
			return;
		}
	}
}



bool gameover()  
{
	int i, j, f = 0;
	if (y>height-1) 
	{
		world[x][height-1] = '@';  
		world[x][height] = '#';
		f = 1;           
		goto quit;
	}
	else
	{     
		int p = 0;
		for (j = 0, j < height, j++) if (world[x][j] == ' ') p++;
			if (p>2 && (world[x][y] == '#' || world[x][y] == '@'))
		{
			c[x][y] = '#';
			c[x - 1][height-1] = '@';
			f = 1;
			goto quit;
		}
	}
quit:
	if (f == 1) return true;
	else return false;
}


