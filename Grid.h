#ifndef GRID_H
#define GRID_H

#include <vector>

using namespace std;

class Grid {
public:
	Grid(int width, int height, char wallSimbol);
	void render();

private:
	int width;
	int height;
	vector<vector<char>> elements;
};




#endif // !GRID_H
