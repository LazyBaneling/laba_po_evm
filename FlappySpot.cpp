// ConsoleApplication8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;


int pos; uptime; centre, edge1, edge2;
char symbol, world[1000][1000];
const interval = 200; maxheight = 30; obstacle = 2; length = 40;
int world[maxheight][length];

void fly_up()
{
	symbol = getchar();
	switch (symbol)
	{
	case ' ': if (pos != maxpos)  uptime += 3;   break;
	}
}
void changepos()
{
	if (uptime > 0) { pos += 2; --uptime };
	else pos -= 2;
}
void make_an_obstacle()
{
	centre = rand();
	if (centre < 0) centre *= -1;
	centre %= maxheight;
	if (centre < 3) centre = 3;
	if (centre > maxheight - 3) centre = maxheight - 3;
	edge1 = centre + 3;
	edge2 = centre - 3;
}

void make_world()
{
	
	for (int j = 0; j <= length, ++j)
	{
		if (distance == 7) 
		{ 
			make_an_obstacle();
			distance = 0;
			for (int i = 0, i <= edge1, ++i) world[i][j] = "#";
			for (int i = maxheight, i >= 0, --i)  world[i][j] = "#";
				

		}
		distance++;


	}

}

void shift_world()
{
	for (int j = 0, j < length-1, ++j)
	 for (int i = 0, i < maxheight, ++i) world[i][j] = world[i][j+1];
	if (distance==7)
	{
		make_an_obstacle();
		distance = 0;
		for (int i = 0, i <= edge1, ++i) world[i][j] = "#";
		for (int i = maxheight, i >= 0, --i)  world[i][j] = "#";
	}
	distance++;
}

void show_world()
{
	system(cls);
	for (int i = 0, i < length, ++i)
	{
		for (int j = 0, j < maxheight, ++j) cout << world[i][j];
		cout << endl;
	}
}








int main()
{
	make_world();
	for (; ; );
	shift_world();
	show_world();
	getchar();
	getchar();

    return 0;
}

