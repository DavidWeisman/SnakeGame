#include <iostream>
#include <ctime>
#include <windows.h>
#include "Food.h"

void Food::getRandomCoordinates(FoodCoordinate &foodCordinate) {
	int Xmin = 1;
	int Ymin = 2;
	srand(static_cast <unsigned int> (time(0)));

	int Xcoordinates = rand() % (maxWidth - Xmin + 1) + Xmin;
	int Ycoordinates = rand() % (maxHeight - Ymin + 1) + Ymin;
	
	foodCordinate.x = Xcoordinates;
	foodCordinate.y = Ycoordinates;
}

Food::Food(char foodSimbol, int width, int height) {
	this->foodSimbol = foodSimbol;
	maxWidth = width - 2;
	maxHeight = height - 2;

	getRandomCoordinates(food);
}

void Food::spawn() {
	getRandomCoordinates(food);
}

void Food::drawFood() {
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		return;
	}


	int previusX = csbi.dwCursorPosition.X;
	int previusY = csbi.dwCursorPosition.Y;

	csbi.dwCursorPosition.X = food.x;
	csbi.dwCursorPosition.Y = food.y;

	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
	SetConsoleTextAttribute(hStdout, 12);
	std::cout << foodSimbol;
	SetConsoleTextAttribute(hStdout, 15);


	csbi.dwCursorPosition.X = previusX;
	csbi.dwCursorPosition.Y = previusY;

	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}

FoodCoordinate Food::getFoodCoordinates() {
	return food;
}