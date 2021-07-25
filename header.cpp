#include "header.h"
#include <iostream>

using namespace std;

int header::appdesc()
{
	cout << "\t\t *** GET LOST ***\n\n";
	cout << "  This application generates mazes using\n";
	cout << "  the concept of direct recursion.  For \n";
	cout << "  our initial proof of concept, we offer\n";
	cout << "  two options for maze dimensions...\n\n";

	cout << "  1)\t30 x 30\n";
	cout << "  2)\t25 x 25\n\n";

	cout << "  Please choose an option (1 or 2):\t";
	cin >> userChoice;
	cout << "  User choice is " << userChoice << "\n\n";
	return userChoice;
}

int header::verifyChoice(int userChoice)
{
	if (userChoice == 1 || userChoice == 2)
	{
		return userChoice;		// return a valid user choice
	}
	else if (userChoice == 4)										// secretsquirrel -programtermination switch ( press 4 )
	{
		exit(0);													// exit program
	}
	else
	{
		cin.clear();												// clear buffer of any content
		cin.ignore(numeric_limits<streamsize>::max(), '\n');		// clear buffer of any content
		system("CLS");												// clear the console
		userChoice = 0;												// reset userChoice val to null
		appdesc();													// invoke appDesc() function again
		return 1;
	}
}




