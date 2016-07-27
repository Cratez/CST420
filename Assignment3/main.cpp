
//
// CST 407 - Assignment #3
//
// Michael Hoffman
//
// File: main.cpp
//
// Race analyzer main program.
//


#include  <iostream>
#include  <cassert>
#include  <cstdlib>
#include  "mainDisplay.h"


//
// If PROMPT_FILENAME is defined, the user will be prompted to
// enter the names of the stages and riders data files. If
// PROMPT_FILENAME is not defined, the default names specified
// by STAGE_FILENAME and RIDER_FILENAME are used.
//
//#define  PROMPT_FILENAME
#define  STAGE_FILENAME       "stages.dat"
#define  RIDER_FILENAME       "riders.dat"


//
// Typedef for menu choices
//
enum  MenuChoice
{
	menuDisplaySummary_ = '1',
	menuDisplayRiders_ = '2',
	menuDisplayTeams_ = '3',

	menuMin_ = menuDisplaySummary_,
	menuMax_ = menuDisplayTeams_,

	menuQuit_ = 'Q'
};


enum  FileType
{
	stage_,
	rider_
};


//
// Fetch a file name from the user
//
static const  string  getFilename(FileType  type)
{
	string  filename;

#ifndef  PROMPT_FILENAME

	filename = (type == stage_ ? STAGE_FILENAME : RIDER_FILENAME);

#else

	cout << "Enter "
		<< (type == stage_ ? "stage" : "rider")
		<< " filename: ";

	cin >> filename;

#endif

	return  filename;
}


//
// Display the menu
//
static  void  menu()
{
	cout << endl
		<< "***********************" << endl
		<< endl
		<< endl
		<< "Menu: " << endl
		<< endl
		<< "  1. Summary info" << endl
		<< "  2. Rider results" << endl
		<< "  3. Team results" << endl
		<< "  Q. Quit" << endl;
}


//
// Get user's menu choice
//
static MenuChoice  getChoice()
{
	menu();

	char  choice;

	while (true)
	{
		cout << endl
			<< "Enter choice: ";

		cin >> choice;
		cin.ignore();

		choice = toupper(choice);

		if (choice == menuQuit_)  break;

		if (choice >= menuMin_  &&  choice <= menuMax_)  break;

		cout << endl
			<< "  *** Invalid option. Try Again. ***"
			<< endl;
	}

	return  MenuChoice(choice);
}


//
// Main program
//
int  main()
{
	try
	{
		const string  stageFilename = getFilename(stage_);
		const string  riderFilename = getFilename(rider_);


		//
		// Setup the race data analyzer
		//
		RaceAnalyzer  raceData(stageFilename, riderFilename);

		bool  done = false;


		//
		// Loop until the userwants to quite
		//
		while (!done)
		{
			//
			// Get a process the user's menu choice
			//
			switch (getChoice())
			{
			case  menuDisplaySummary_:  displaySummary(raceData);
				break;

			case  menuDisplayRiders_:  displayRiderData(raceData);
				break;

			case  menuDisplayTeams_:  displayTeamData(raceData);
				break;

			case  menuQuit_:  done = true;
				break;

			default:  assert(true);
			}
		}

	}
	catch (...)
	{
		system("pause");
		return  EXIT_FAILURE;
	}

	return  EXIT_SUCCESS;
}