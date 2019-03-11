// Console graphics - for drawing text and boxes on the console window
// Version 0.1

#ifndef CONSOLE_GRAPHICS_H
#define CONSOLE_GRAPHICS_H

#include <Windows.h>
#include <iostream>
#include <cassert>

using namespace std;


#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKCYAN 3
#define DARKRED 4
#define DARKMAGENTA 5
#define DARKYELLOW 6
#define GRAY 7
#define DARKGRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15

//========================================================================================
// prototypes

bool printText(const char text[], int row, int col, int fgColor=WHITE, int bgColor=BLACK);
	//Prints given text at given location, using given colors
	//row - 0-24
	//col - 0-80
	//fgColor and bgColor - foreground and background colors (from above list)
	//returns true if successful

bool drawBlock(int top, int left, int height, int width, int color=BLACK);
	//Draws a solid Block on the screen
	//top - 0-24
	//left - 0-80
	//color - from above list
	//returns true if successful

bool drawBox(int top, int left, int height, int width, int fgColor=WHITE, int bgColor=BLACK);
	//Draws a double-lined on the screen
	//top - 0-24
	//left - 0-80
	//fgcolor - color of lines (from above list)
	//bgcolor - background color (from above list)
	//returns true if successful

bool cls(int color=BLACK);
	//clears the screen
	//color - color to make the screen
	//returns true if successful



#endif