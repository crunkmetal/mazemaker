// maze generator 1.2
// create a maze using direct recursion
/*
	Due Aug 1 by 11:59pm
	- Using Direct Recursion, write a program to auto-create and display the following mazes
		- 30 x 30
		- 25 x 25
		- maze shall not be hard-coded
	- Your maze should display on a console window using ASCII characters.
	- Your maze should be 2D. Extra credit for 3D Mazes
	- It should include ASCII characters as walls and blank spaces as paths.
		- It does not have to be a solvable maze, however, extra credit for a solvable maze.
*/

// TODO: 30x30 maze: left and top borders are two lines thick - should be one line thick
// TODO: 25x25 maze: right and bottom borders are pushed to far to right
// TODO: change userinput from cin to one-click char press
// updated: created an exitPunch() to make a maze exit

#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>	// bitshifting
#include <algorithm>
#include <unordered_map>
#include "Header.h"

using namespace std;

// constants
// #define G_WIDTH 30	// TODO: make not hard-coded
// #define G_HEIGHT 20 // TODO: make not hard-coded
#define LOOKUP 0
#define LOOKRIGHT 1
#define LOOKDOWN 2
#define LOOKLEFT 3

// global vars
int G_WIDTH;
int G_HEIGHT;
char wall = 'X';
int starter;
// int goo = 0;



// function prototypes
int coordsToArray(int, int);
bool isInChamber(int, int);
void scout(int, int, char*);
void exitPunch(vector<char>&);
void showMaze(vector<char>const&);
unordered_map<char, int> initialize(int);

// main() is program entry point
int main()
{
	srand(time(0));						// seed random num gen
	Header Welcome;						// instantiate object
	int z = 0;							// game loop counter start

	do									// game loop
	{
		Welcome.appdesc();
		int mazeChoice = Welcome.verifyChoice(Welcome.userChoice);
		unordered_map<char, int> mapping = initialize(mazeChoice);
		G_WIDTH = mapping['x'];
		G_HEIGHT = mapping['y'];

		int block = G_HEIGHT * G_WIDTH;
		vector<char> maze(block, 'X');
		char* p_maze = maze.data();
		
		system("CLS");					// clear console of app/user choice info
		cout << "\n  Displaying a " << G_WIDTH << " x " << G_HEIGHT << " maze:\n";

		scout(4, 0, p_maze);  // TODO:  changing x value messes up maze (4 works for now)
		exitPunch(maze);
		showMaze(maze);


		cout << "\n\n\n";

		system("pause >nul | echo. Continue...");

		system("CLS");
		cout << "\n\n";
		z++;							// preventing recursive loop
	} while (z < 5);					// game loop counter end#
	cout << "\n\n";

	return 0;
}										// end of main

// function to make an exit
void exitPunch(vector<char>& maze)
{
	int min = (maze.size()) - (G_WIDTH-1);
	int max = (maze.size() - 1);
	int randNum = rand() % ( max - min + 1) + min;

	// if (  maze[(randNum - G_WIDTH)] == ' ')	// grid above random grid is empty   <-- 30 x 30
	if (maze[(randNum - (G_WIDTH))] == ' ')	// grid above random grid is empty
	{
		maze[randNum] = 'U';
	}
	else
	{
		exitPunch(maze);
	}
}

// Function to return multiple values using a map
unordered_map<char, int> initialize(int userChoice)
{
	unordered_map<char, int> mapping;

	if (userChoice == 1)
	{
		mapping['x'] = 30;
		mapping['y'] = 30;
	}
	else
	{
		mapping['x'] = 25;
		mapping['y'] = 25;
	}
	return mapping;
}

// function to display to console, results of recursive functionality
void showMaze(vector<char> const& maze)
{
	if (G_WIDTH == 30)
	{
		int gridCount = 1;
		for (int a = 0; a < maze.size(); a++)
		{
			if (a == G_WIDTH)
			{
				// cout << 'A';
				cout << "\n\t";
				gridCount = 2;
			}
			else if (a == (G_WIDTH * gridCount))
			{
				// cout << 'B';
				cout << "\n\t";

				gridCount++;
			}
			else if (a < G_WIDTH)
			{
				//cout << 'U';
			}
			else if (maze[a] == 'U')
			{
				cout << ' ';
			}
			else
			{
				cout << maze.at(a);
			}
		}
	}
	else	// do this if maze dims are not of 30x30 choice
	{
		int smGridCount = 0;
		for (int a = 0; a <= maze.size(); a++)
		{
			if (a == G_WIDTH)
			{
				// cout << 'P';
				cout << "\n\t";
				smGridCount = 2;
			}
			else if (a == (G_WIDTH * smGridCount))
			{
				cout << 'X';		// cheat
				cout << "\n\t";
				smGridCount++;
			}
			else if (a > ( maze.size() - G_WIDTH ) && a < maze.size())
			{
				if (maze[a] == 'U')
				{
					cout << ' ';
				}
				else
				{
					cout << 'X';		// testing
				}
			}
			else if (a < G_WIDTH)
			{
				// cout << 'U';
			}
			else
			{
				cout << maze.at(a);
			}
		}
	}


	



	// MH assistance version below
	//std::cout << "\n\n\n\n";
	/*int p = 0;
	for (std::vector<char>::const_iterator a = maze.begin(); a != maze.end(); a++)
	{
		if (p == G_WIDTH-1)
		{
			std::cout << *a << std::endl;
			p = 0;
		}

		else if (p != G_WIDTH-1)
		{
			std::cout << *a;
			p++;
		}
		
	}*/
	//std::cout << p << std::endl;

}




// recursive function to scout the gridblock and carve out a path
void scout(int x, int y, char* maze)	// scout(4,0, maze)
{
	const int X = x;	// unused
	const int Y = y;	// unused

	starter = coordsToArray(x, y);		// starter = 4
	maze[starter] = ' ';									// value of maze[4] is startergrid

	// create a local array containing four directions of travel
	int compass[4]{0, 1, 2, 3};
	/*compass[0] = LOOKUP;
	compass[1] = LOOKRIGHT;
	compass[2] = LOOKDOWN;
	compass[3] = LOOKLEFT*/;

	//// shuffle the order of array contents
	for (int i = 0; i < 4; i++)
	{
		int b = rand() % 3;
		int temp = compass[b];
		compass[b] = compass[i];
		compass[i] = temp;
	}

	// loop thru each direction, scouting next move
	// offsets increment x,y values from current index
	for (int i = 0; i < 4; i++)
	{
		int offsetX = 0;
		int offsetY = 0;

		switch (compass[i])
		{
			case LOOKUP:
			{
				offsetY = -1;	
				break;
			}
			case LOOKDOWN:
			{
				offsetY = 1;
				break;
			}
			case LOOKRIGHT:
			{
				offsetX = 1;
				break;
			}
			case LOOKLEFT:
			{
				offsetX = -1;
				break;
			}
		}	// end of switch
	
		int x2 = x + (offsetX<<1);	// bitshifter	4 + ()
		int y2 = y + (offsetY<<1);	// bitshifter

		//goo++;
		// if next move is within gridblock...
		if (isInChamber(x2, y2))
		{
			//std::cout << "x " << x << " x2 " << x2 << "\n y " << y << " y2 " << y2 << std::endl;
			if (maze[coordsToArray(x2, y2) ] == 'X')
			{
				maze[ coordsToArray(x2 - offsetX, y2 - offsetY) ] = ' ';	// replace wall between current and next move
				scout(x2, y2, maze);												// recursively scout next move
			}
		}
	}
}



// function that returns true/false based on results
// of location x and y
// returns true if both x and y are within block
bool isInChamber(int x, int y)		// x2,y2
{
	// if (y <= 0 || y >= G_HEIGHT || x <= 0 || x >= (G_WIDTH-1))	// works for 30x30
	if (y <= 0 || y >= G_HEIGHT || x <= 0 || x >= G_WIDTH)	// attempt for 25x25
	{
		return false;
	}
	/*else if (x <= 0 || x >= G_WIDTH)
	{
		return false;
	}*/
	else
	{
		return true;
	}
}

// function to convert x/y coordinates to an array index equivalent
int coordsToArray(int x, int y)	// 4,0
{
	return y * G_WIDTH + x;		// 4
}
