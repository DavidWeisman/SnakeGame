#ifndef FOOD_H
#define FOOD_H



typedef struct FoodCoordinate {
	int x;
	int y;
};


class Food {
public:
	Food(char foodSimbol, int width, int height);
	void spawn();
	void drawFood();
	FoodCoordinate getFoodCoordinates();
	void getRandomCoordinates(FoodCoordinate& foodCordinate);

private:
	FoodCoordinate food;
	char foodSimbol;
	int maxWidth;
	int maxHeight;
};


#endif // !FOOD_H
