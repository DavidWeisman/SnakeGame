#include <iostream>
#include "Snake.h"
#include <windows.h>


Snake::Snake() {
	Coordinate head;
	head.x = 10;
	head.y = 10;
	head.direction = RIGHT;

	coordinates.push_back(head);
	snakeDirection = RIGHT;
}


void Snake::move() {
	Coordinate previusCordinate = coordinates[0];
	Coordinate tempCordinate;

	switch (snakeDirection)
	{
	case UP:
		coordinates[0].y--;
		break;
	case DOWN:
		coordinates[0].y++;
		break;
	case LEFT:
		coordinates[0].x--;
		break;
	case RIGHT:
		coordinates[0].x++;
		break;
	default:
		break;
	}

	for (int i = 1; i < coordinates.size(); i++) {
		tempCordinate = coordinates[i];
		coordinates[i] = previusCordinate;
		previusCordinate = tempCordinate;
	}
}


void Snake::grow() {
	Coordinate lastElement = coordinates.back();
	
	Coordinate newCordinate;
	newCordinate.direction = lastElement.direction;


	switch (lastElement.direction)
	{
	case UP:
		newCordinate.x = lastElement.x;
		newCordinate.y = lastElement.y - 1;
		break;
	case DOWN:
		newCordinate.x = lastElement.x;
		newCordinate.y = lastElement.y + 1;
		break;
	case LEFT:
		newCordinate.x = lastElement.x + 1;
		newCordinate.y = lastElement.y;
		break;
	case RIGHT:
		newCordinate.x = lastElement.x - 1;
		newCordinate.y = lastElement.y;
		break;
	default:
		break;
	}

	coordinates.push_back(newCordinate);
}


Coordinate Snake::get_head() {
	return coordinates[0];
}

Coordinate Snake::get_tail() {
	return coordinates.back();
}


Coordinate Snake::get_one_befor_head() {
	return coordinates[1];
}


void Snake::SetDirection(Direction direction) {
	snakeDirection = direction;
}


bool Snake::isSnakeKrash() {
	for (int i = 1; i < coordinates.size(); i++) {
		if (coordinates[i].x == coordinates[0].x && coordinates[i].y == coordinates[0].y) {
			return true;
		}
	}
	return false;
}


Direction Snake::getDirection() {
	return snakeDirection;
}

void Snake::resetSanke() {
	coordinates.clear();
	Coordinate head;
	head.x = 10;
	head.y = 10;
	head.direction = RIGHT;

	coordinates.push_back(head);
	snakeDirection = RIGHT;
}