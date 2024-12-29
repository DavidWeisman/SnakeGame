#include <iostream>
#include "Grid.h"
#include <windows.h>
#include <thread>


using namespace std;



Grid::Grid(int width, int height, char wallSimbol) {
	this->width = width;
	this->height = height;

     
	for (int i = 0; i < height; i++) { 
		vector<char> v;
		for (int j = 0; j < width; j++) {
			
			
			if (i == 0 || i == (height - 1)) {
				v.push_back(wallSimbol);
			}
			else {
				if (j == 0 || j == (width - 1)) {
					v.push_back(wallSimbol);
				}
				else {
					v.push_back(' ');
				}
			}
 		
		}
		elements.push_back(v);
	}

}

void Grid::render() {
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		return;
	} 

	int previusX = csbi.dwCursorPosition.X;
	int previusY = csbi.dwCursorPosition.Y;

	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << elements[i][j];
		}
		cout << endl;
	}

	csbi.dwCursorPosition.X = width;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << "#################";
	csbi.dwCursorPosition.Y = 1;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << " You Score:     #";
	csbi.dwCursorPosition.Y = 2;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << " High Scoer:    #";
	csbi.dwCursorPosition.Y = 3;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << "#################";
	csbi.dwCursorPosition.Y = 4;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << "  RECORD TABLE  #";
	csbi.dwCursorPosition.Y = 5;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << "----------------#";
	for (int i = 0; i < 14; i++) {
		csbi.dwCursorPosition.Y = 6 + i;
		SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
		cout << "                #";
	}
	csbi.dwCursorPosition.Y = 19;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	cout << "#################";
}






