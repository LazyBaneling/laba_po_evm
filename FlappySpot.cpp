#include "stdafx.h"
#include <iostream> 
#include <cstdlib>   // чтобы библиотеки тоже могли юзать std
#include <windows.h> // много разных макросов и штук, чтобы все работало
#include <conio.h>   // для гетча и кбхита
#include <ctime>     // очевидно
#include <fstream>   // для работы с файлами
#include <iomanip>   // это в общем тоже для времени

using namespace std;

ifstream inp;
ofstream outp;

char world[30][21];
int check[30][21];
int highscore;
int key = 0, score = 0, t = 0, ft = 0, x = 0, y = 0, godmode=0;
bool err;

void game();
void show_world();
void make_world();
void changepos();
bool gameover();
void checkscore();
void menu();
void endgame();

int main()
{
	srand(time(0));
	inp.open("C:/Users/user/Documents/Visual Studio 2015/Projects/ConsoleApplication16/ConsoleApplication16/highscore.txt");
	if (inp.is_open())
	{
		inp >> highscore;
		inp.close();                          // открываем файл с хайскором, а если он не открылся (а потому что не захотел, кто его знает), то хайскор равен 0
		err = false;
	}
	else
	{
		highscore = 0;
		err = true;
	}

	int a = 0;
	char sl;
	while (1)
	{
		if (a == 0) goto play;
		if (a>0)
		{
			score = 0;
			cout << "Do you want to play again? [y/n] ";
			cin >> sl;
			if (sl == 'n') return 0;
			else goto play;
		}
	play:
		menu();
		cin >> sl;                                  //         меню, все дела
		switch (sl)
		{
		case '1':
		{
			game();
			break;
		}
		case '2':
		{
			return 0;
			break;
		}
		default:
		{
			goto play;
			break;
		}
		}
		a++;
	}
}

void game()                 // скажем так "движок" игры
{
	int i, j;
	char s;
	for (j = 0; j<21; j++)
	{
		for (i = 0; i<30; i++)
		{
			if (j<20)
			{                                                    
				world[i][j] = ' ';
				check[i][j] = 0;
			}
			if (j == 20)
			{
				world[i][j] = '#';
				check[i][j] = 2;
			}
		}
	}
	world[10][10] = '@';
	show_world();
	while (1)
	{
		s = '~'; 
		Sleep(0.2 * 1000); // тут можно поменять скорость игры 
		t++;
		if (_kbhit())
		{
			s = _getch();
			if (s != '~') key = 1; // можем не париться с управлением и играть любой кнопкой кроме тильды
			if (s == 'g') godmode = 1;

		}
		for (i = 0; i<30; i++)
		{
			world[i][20] = '#';
			check[i][20] = 2;
		}
		changepos();
		checkscore();
		if (gameover() == true) 
		{
			if (score>highscore) highscore = score;
			if (err == false)
			{
				outp.open("C:/Users/user/Documents/Visual Studio 2015/Projects/ConsoleApplication16/ConsoleApplication16/highscore.txt");
				outp << highscore;
				outp.close();
			}
			show_world();
			endgame();
			return;
		}
		make_world();
		if (score>highscore) highscore = score;
		show_world();

		if (key>0) key++;
		if (key == 3) key = 0;
	}
}

void show_world() //рисуем мир и кол-во очков
{
	int i, j;
	system("cls");
	for (j = 0; j<21; j++)
	{
		for (i = 0; i<30; i++)
		{
			if (i<29) cout << world[i][j];
			if (i == 29) cout << world[i][j] << endl;
		}
	}
	cout << "" << endl;
	cout << "Your Score: " << score;
	if (godmode == 1) cout << "\n HAHA NOW YOU CANNOT DIE CAUSE YOU'RE GOD MWAHAHHAH \n (it means that you have to shut down the game to quit or play forever)";
}

void make_world()  // делаем стены и двигаем их
{
	int i, j, centre;
	if (t == 10)
	{
		centre = (rand() % 11) + 5;
		for (j = 0; j<20; j++)
		{
			world[29][j] = '#';
			check[29][j] = 2;
		}
		world[29][centre - 1] = ' ';
		world[29][centre] = ' ';
		world[29][centre + 1] = ' ';
		check[29][centre - 1] = 0;
		check[29][centre] = 0;
		check[29][centre + 1] = 0;
		t = 0;
	}

	{
		for (j = 0; j<20; j++)
		{
			for (i = 0; i<30; i++)
			{
				if (world[i][j] == '#')
				{
					if ((i>0) && (godmode==0 || world[i-1][j] != '@'))
					{
						world[i - 1][j] = '#';
						check[i - 1][j] = 2;
						world[i][j] = ' ';
						check[i][j] = 0;
					}
					if (i == 0)
					{
						world[i][j] = ' ';
						check[i][j] = 0;
					}
				}
			}
		}
	}
}

void changepos()                       // птица летает вверх/вниз
{
	int i, j;
	if (key>0)
	{
		ft = 0;
		for (j = 0; j<20; j++)
		{
			for (i = 0; i<30; i++)
			{
				if (world[i][j] == '@')
				{
					if (j>0)
					{
						world[i][j - 1] = '@';
						world[i][j] = ' ';
						x = i;
						y = j - 1;
						return;
					}
				}
			}
		}
	}
	else
	{
		ft++;
		for (j = 0; j<20; j++)
		{
			for (i = 0; i<30; i++)
			{
				if (world[i][j] == '@')
				{
					if (j<20)
					{
						if (ft<3)
						{
							world[i][j + 1] = '@';
							world[i][j] = ' ';
							x = i;
							y = j + 1;
							return;
						}
						else if (ft>2 && ft<5)
						{
							world[i][j + 2] = '@';
							world[i][j] = ' ';
							x = i;
							y = j + 2;
							return;
						}
						else if (ft>4)
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

void checkscore()   // тут понятно
{
	int j;
	for (j = 0; j<20; j++)
	{
		if (world[x][j] == '#')
		{
			score++;
			return;
		}
	}
}

bool gameover()       //проверка на целостность птичьей головы
{
	int f = 0;
	if (godmode == 1) return false; // хех
	if (y>19)
	{
		world[x][19] = '@';
		world[x][20] = '#';
		f = 1;
		if (f == 1) return true;
		else return false;
	}
	else
	{
		if (check[x][y]>0 && (world[x][y] == '#' || world[x][y] == '@'))
		{
			world[x][y] = '#';
			world[x - 1][19] = '@';
			f = 1;
			if (f == 1) return true;
			else return false;
		}
	}
}

void endgame()       // очевидно
{
	show_world();
	cout << "" << endl << endl;
	cout << "GAME OVER  ";
	cout << "" << endl << endl;
	cout << "YOUR SCORE: " << score << endl << endl;
	cout << "HIGH SCORE: " << highscore << endl;
	cout << "" << endl << endl;
}

void menu()     // тоже очевидно
{
	system("cls");
	cout << "" << endl;
	cout << "FLAPPY SPOT";
	cout << "" << endl << endl;
	cout << "High Score:  " << highscore << endl << endl;
	cout << "" << endl << endl;
	cout << "MENU:    " << endl << endl;
	cout << "1: Start Game  " << endl << endl;
	cout << "2: Exit        " << endl << endl;
}
