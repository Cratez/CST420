// Console graphics - for drawing text and boxes on the console window
// Version 0.1

#include "console_graphics.h"

//===================================================================
// helper functions

//----------------------------------------------------------------
// positions cursor at given position
void gotoRowCol(short row, short col){
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD c;

	c.X = col; 
	c.Y = row;
	SetConsoleCursorPosition(hStdout,c);

	return;
}

//----------------------------------------------------------------
// sets foreground and background color
void setColor(short fgColor, short bgColor) {
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

	//bits 8-5 are are background, (4-1) are foreground
	SetConsoleTextAttribute(hStdout, (bgColor << 4) | fgColor);
}

//===============================================================
// "public" functions (prototypes in .h file

//----------------------------------------------------------------
// prints text on the screen at given location
bool printText(const char text[], int row, int col, int fgColor, int bgColor)
{
	assert(row>=0 && row <= 24);
	assert(col>=0 && col <= 79);

	gotoRowCol(row, col);
	setColor(fgColor, bgColor);
	cout << text;

	return true;
}

//----------------------------------------------------------------
// draws a block on the screen
bool drawBlock(int top, int left, int height, int width, int color) {
	assert(top>=0 && top <=24);
	assert(left>=0 && left <=79);

	for(int row=top; row<top+height; row++)
		for(int col=left; col<left+width; col++)
			printText(" ", row, col, color, color);
	
	gotoRowCol(24,0);
	
	return true;
}

//----------------------------------------------------------------
// draws a double-lined box on the screen
bool drawBox(int top, int left, int height, int width, int fgColor, int bgColor) {
	//console characters for double-line box
	unsigned char vertLine[]= {186,0};
	unsigned char cornerUR[]= {187,0};
	unsigned char cornerLR[]= {188,0};
	unsigned char cornerUL[]= {201,0};
	unsigned char cornerLL[]= {200,0};
	unsigned char horzLine[]= {205,0};
	int row, col;

	//top of box
	row=top;
	col=left;
	printText((char*)cornerUL, row, col, fgColor, bgColor);
	for(col=left+1; col<left+width-1; col++)
			printText((char*)horzLine, row, col, fgColor, bgColor);
	printText((char*)cornerUR, row, col, fgColor, bgColor);
	
	//left side
	col=left;
	for(row=top+1; row<top+height-1; row++)
		printText((char*)vertLine, row, col, fgColor, bgColor);

	//right side
	col=left+width-1;
	for(row=top+1; row<top+height-1; row++)
		printText((char*)vertLine, row, col, fgColor, bgColor);

	//bottom of box
	row=top+height-1;
	col=left;
	printText((char*)cornerLL, row, col, fgColor, bgColor);
	for(col=left+1; col<left+width-1; col++)
			printText((char*)horzLine, row, col, fgColor, bgColor);
	printText((char*)cornerLR, row, col, fgColor, bgColor);
	
	return true;
}

//----------------------------------------------------------------
// clears the screen
bool cls(int color) {
	return drawBlock(0,0,24,80,color);
}

//=================================================================
// test code
// comment out to use functions in another project

//----------------------------------------------------------------
/*void main() {
	int row=1;
	int col=1;
	char str[]="  Sample  ";
	int fgColor=0;
	int bgColor=0;



	//first 8 colors are dark.
	//last 8 colors are bright

	//dark text on dark backgrond
	for (bgColor=0;bgColor<8; bgColor++) {
		row=0;
		col=bgColor * strlen(str);
		//print all possible colors on current background
		//first 8 are dim.  Last 8 are bright
		for (fgColor=0; fgColor<8; fgColor++) {
			printText(str, row, col, fgColor, bgColor);
			row++;
		}
	}

	//bright text on bright background colors
	for (bgColor=8; bgColor<16; bgColor++) {
		row=8;
		col=(bgColor-8) * strlen(str);
		//print show all 8 bright foreground colors
		for (fgColor=8; fgColor<16; fgColor++) {
			printText(str, row, col, fgColor, bgColor);
			row++;
		}
	}

	//bright text on dark background colors
	for (bgColor=0; bgColor<8; bgColor++) {
		row=16;
		col=bgColor * strlen(str);
		//print show all 8 bright foreground colors
		for (fgColor=8; fgColor<16; fgColor++) {
			printText(str, row, col, fgColor, bgColor);
			row++;
		}
	}

	//printText("press enter for block and box tests",23,1,WHITE, BLACK);
	cin.get(); 

	cls(BLUE);

	drawBlock(3,3,10,30,GREEN);
	drawBox(3,3,10,30,WHITE,GREEN);

	drawBlock(10,10,5,20,BLACK);
	drawBlock(1,78,1,1,YELLOW);
	drawBlock(6,40,15,30,RED);
	drawBox(5,5,3,3);
	
	cin.get();
}*/
