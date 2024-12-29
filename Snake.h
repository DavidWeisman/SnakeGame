#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
using namespace std;


enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};



typedef struct Coordinate {
	int x;
	int y;
	Direction direction;
};



class Snake {
public:
	Snake();
	void move();
	void grow();
	Coordinate get_head();
	Coordinate get_one_befor_head();
	Coordinate get_tail();
	void SetDirection(Direction direction);
	bool isSnakeKrash();
	Direction getDirection();
	void resetSanke();



private:
	vector<Coordinate> coordinates;
	Direction snakeDirection;
};





#endif // !SNAKE_H

