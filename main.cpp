// maze generator 1.0
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


/*
	https://www.cefns.nau.edu/~pek7/CS200/Project%209.pdf
	For example, in a rectangular maze, build at random points two walls that are perpendicular to each other.
	These two walls divide the large chamber into four smaller chambers separated by four walls. Choose three of the four walls at random, and open a one cell-wide hole at a random point in each of the three. Continue in this manner recursively, until every chamber has a width of one cell in either of the two directions.
*/

#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>	// bitshifting
#include <algorithm>
#include <unordered_map>
#include "header.h"

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
// vector<char> maze;
char wall = 'X';
int starter;


// function prototypes
// void blockGrid();
int coordsToArray(int, int);
bool isInChamber(int, int);
void scout(int, int, char*);
// void showMaze();
void showMaze(vector<char> const&);

unordered_map<char, int> initialize(int);



int main()
{
	srand(time(0));						// seed random num gen
	header Welcome;						// instantiate object
	int z = 0;							// game loop counter start

	do									// game loop
	{
		Welcome.appdesc();
		int mazeChoice = Welcome.verifyChoice(Welcome.userChoice);
		unordered_map<char, int> mapping = initialize(mazeChoice);
		G_WIDTH = mapping['x'];
		G_HEIGHT = mapping['y'];
		cout << "  Creating a " << G_WIDTH << " x " << G_HEIGHT << " maze.\n\n";
		int block = G_HEIGHT * G_WIDTH;
		vector<char> maze(block, 'X');
		char* p_maze = maze.data();
		// blockGrid();  < -- to delete becuz of line above
		// showMaze(maze);
		cout << "\n";
		// scout(6, 0, p_maze);
		system("CLS");
		scout(6, 0, p_maze);
		showMaze(maze);
		cout << "\n\n";
		system("pause");
		system("CLS");
		cout << "\n\n";
		z++;							// preventing recursive loop
	} while (z < 5);					// game loop counter end#
	cout << "\n\n";

	return 0;
}	// end of main

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

//// populate a block to start with
//void blockGrid()
//{
//	// for array
//	//for (int a = 0; a < sizeof(maze); a++)	// for each element in maze[]...
//	//{
//	//		maze[a] = wall;					// assign a value of char #
//	//}
//	fill(maze.begin(), maze.end(), wall);
//}

// function to display to console, results of recursive functionality
void showMaze(vector<char> const& maze)
{
	int gridCount = 0;

	for (int a = 0; a < maze.size(); a++)	// cout << maze.at(a) << ' ';
	{
		if (a == G_WIDTH)
		{
			cout << "\n\t" << maze.at(a);
			gridCount = 2;
		}
		else if (a == (G_WIDTH * gridCount))
		{
			cout << "\n\t" << maze.at(a);
			gridCount++;
		}
		else
			cout << maze.at(a);
	}
}


/*
	**** it would appear that the problem is my vector access below --------------------------------------------------------------------------------
*/


// recursive function to scout the gridblock and carve out a path
void scout(int x, int y, char* maze)
{

	// coordsToArray(x, y);
	starter = coordsToArray(x, y);
	// cout << "  coordinates to array:\t" << starter << "\n";
	// system("pause");
	maze[starter] = ' ';									// value of maze[36] = ' ' open space
	//maze.at(starter) = ' ';
	// create a local array containing four directions of travel
	int compass[4]{};
	compass[0] = LOOKUP;
	compass[1] = LOOKRIGHT;
	compass[2] = LOOKDOWN;
	compass[3] = LOOKLEFT;

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
	
		int x2 = x + (offsetX<<1);	// bitshifter
		int y2 = y + (offsetY<<1);	// bitshifter
		
		// if next move is within gridblock...
		if (isInChamber(x2, y2))
		{
			// if (maze[coordsToArray(x2, y2)] == 'X')
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
bool isInChamber(int x, int y)
{
	if (y <= 0 || y >= G_HEIGHT)
	{
		return false;
	}
	else if (x <= 0 || x >= G_WIDTH)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// function to convert x/y coordinates to an array index equivalent
int coordsToArray(int x, int y)
{
	return y * G_WIDTH + x;
}
