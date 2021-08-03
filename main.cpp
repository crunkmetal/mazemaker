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

// preprocessor directives
#include <iostream>
#include <vector>
#include <stdint.h>			// for bitshifting
#include <algorithm>
#include <unordered_map>		// for unordered map
#include "Header.h"

using namespace std;

// constants/macros
#define LOOKUP 0
#define LOOKRIGHT 1
#define LOOKDOWN 2
#define LOOKLEFT 3

// global variables
int G_WIDTH;
int G_HEIGHT;
char wall = 'X';
int starter;

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
	int z = 0;						// game loop counter start

	do							// game loop
	{
		Welcome.appdesc();				// invoke appdesc() function  from Header class
		int mazeChoice = Welcome.verifyChoice(Welcome.userChoice);	// assign value of Header class method userChoice to var value mazeChoice
		unordered_map<char, int> mapping = initialize(mazeChoice);	// invoke function to initialize an unordered map
		G_WIDTH = mapping['x'];			// unordered map value assigned to G_WIDTH
		G_HEIGHT = mapping['y'];		// unordered map value assigned to G_HEIGHT

		int block = G_HEIGHT * G_WIDTH;		// assign product of width*height to var block
		vector<char> maze(block, 'X');		// assign the value of 'X' to all elements of vector
		char* p_maze = maze.data();		// assign the values of vector maze elements to pointer to char
		system("CLS");				// clear console of app/user choice info
		cout << "\n  Displaying a " << G_WIDTH << " x " << G_HEIGHT << " maze:\n";

		scout(4, 0, p_maze);			// invoke scout() function w/ parameters (x/y values and char pointer)
		exitPunch(maze);			// invoke function to punch out an exit wall
		showMaze(maze);				// display the results of recursive maze function

		cout << "\n\n\n";
		system("pause >nul | echo. Continue...");	// WinOS specific cmd to pause this application
		system("CLS");					// WinOS specific cmd to clear the console
		cout << "\n\n";
		z++;						//preventing recursive loop
	} while (z < 5);					// game loop counter end#
	cout << "\n\n";

	return 0;						// main() must return an integer
}								// end of main

// function to make an exit
void exitPunch(vector<char>& maze)
{
	int min = (maze.size()) - (G_WIDTH - 1);		// creating a minimum value
	int max = (maze.size() - 1);				// creating a maximum value
	int randNum = rand() % (max - min + 1) + min;		// assign the value of this random number to var randNum

	if (maze[(randNum - (G_WIDTH))] == ' ')			// if the grid above the random grid is empty...
	{
		maze[randNum] = 'U';				// change it's value to 'U' (to be deleted later in exitPunch)
	}
	else							// if grid above the random grid is NOT empty...
	{
		exitPunch(maze);				// repeat until an exit is found
	}
}

// Function to return multiple values using a map
unordered_map<char, int> initialize(int userChoice)
{
	unordered_map<char, int> mapping;			// create an unordered map called mapping

	if (userChoice == 1)					// if the user choice is equal to 1...
	{
		mapping['x'] = 30;				// map x value = 30
		mapping['y'] = 30;				// map y value = 30
	}
	else							// if user choice is NOT equal to 1...
	{
		mapping['x'] = 25;				// map x value = 25
		mapping['y'] = 25;				// map y value = 25
	}
	return mapping;						// return values of unordered map
}

// function to display to console, results of recursive functionality
void showMaze(vector<char> const& maze)
{
	if (G_WIDTH == 30)					// do this if maze dims ARE of 30x30 choice
	{
		int gridCount = 1;				// counter to find end of rows
		for (int a = 0; a < maze.size(); a++)		// for each element of the maze vector...
		{
			if (a == G_WIDTH)			// end of first row
			{
				cout << "\n\t";
				gridCount = 2;			// increment by two after end of first row 
			}
			else if (a == (G_WIDTH * gridCount))	// if element is at the end of row 2, 3, 4, 5, etc.
			{
				cout << "\n\t";
				gridCount++;			// after first row, simply increment counter by one
			}
			else if (a < G_WIDTH)			// for elements of the first row
			{
				//cout << 'U';			// do nothing but print contents of vector
			}
			else if (maze[a] == 'U')		// if char at this element is equal to 'U', replace w/ a space (exit door)
			{
				cout << ' ';
			}
			else
			{
				cout << maze.at(a);		// print contents of element to display
			}
		}
	}
	else							// do this if maze dims are NOT of 30x30 choice
	{
		int smGridCount = 0;				// initialize counter to zero
		for (int a = 0; a <= maze.size(); a++)		// for each element of the maze vector
		{
			if (a == G_WIDTH)			// end of first row
			{
				cout << "\n\t";
				smGridCount = 2;		// increment counter after first row by 2
			}
			else if (a == (G_WIDTH * smGridCount))	// for elements at ends of rows
			{
				cout << 'X';			// cheat
				cout << "\n\t";
				smGridCount++;			// increment counter by one
			}
			else if (a > (maze.size() - G_WIDTH) && a < maze.size())	// if vector element is in the last row...
			{
				if (maze[a] == 'U')		// looking for back door key
				{
					cout << ' ';		// punch out an exit door
				}
				else
				{
					cout << 'X';		// testing
				}
			}
			else if (a < G_WIDTH)			// for first row...
			{
				// cout << 'U';			// do not change original maze contents
			}
			else
			{
				cout << maze.at(a);		// print to dispaly contents of vector element
			}
		}
	}
}

// function to scout the gridblock and carve out a path
void scout(int x, int y, char* maze)				// takes three parameters
{
	starter = coordsToArray(x, y);				// assign value of function results to var starter
	maze[starter] = ' ';					// value of maze element is the starter grid

	// create a local array containing four directions of travel
	int compass[4]{ 0, 1, 2, 3 };				// as seen above in macros

	// shuffle the order of array contents
	for (int i = 0; i < 4; i++)				// for loop to iterate four times
	{
		int b = rand() % 3;				// assign random number modulus to b
		int temp = compass[b];				// compass element (b value) assigned to temp var
		compass[b] = compass[i];			// assign value of compass element (zero - three) to value of compass (b value)
		compass[i] = temp;				// compass element (zero - three) assigned the temp value
	}

	// loop thru each direction, scouting next move
	// offsets increment x,y values from current index
	for (int i = 0; i < 4; i++)
	{
		int offsetX = 0;				// initialize offsetX value to zero
		int offsetY = 0;				// initialize offsetY value to zero
		// switch to determine branching (which direction does maze digger go next)
		switch (compass[i])				// based on current compass value
		{
		case LOOKUP:					// if random choice is UP...
		{
			offsetY = -1;				// offsetY value equals -1
			break;					// break out of this switch statement
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
		}						// end of switch statement

		int x2 = x + (offsetX << 1);			// bitshifter - moving by binary
		int y2 = y + (offsetY << 1);			// bitshifter

		// if next move is within the maze gridblock...
		if (isInChamber(x2, y2))
		{
			if (maze[coordsToArray(x2, y2)] == 'X')				// if vector element is equal to 'X'...
			{
				maze[coordsToArray(x2 - offsetX, y2 - offsetY)] = ' ';	// replace wall between current and next move
				scout(x2, y2, maze);					// recursively scout next move
			}
		}
	}		// end of for loop
}

// function that returns true/false based on results of location x and y
// returns true if both x and y are within block
bool isInChamber(int x, int y)
{
	if (y <= 0 || y >= G_HEIGHT || x <= 0 || x >= G_WIDTH)	// if x or y is outside of grid...
	{
		return false;					// ... grid element is NOT w/in gridblock
	}
	else							// else...
	{
		return true;					// ... grid element IS w/in gridblock
	}
}

// function to convert x/y coordinates to an array index equivalent
int coordsToArray(int x, int y)
{
	return y * G_WIDTH + x;
}
