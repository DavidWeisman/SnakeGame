#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Snake.h"
#include "Grid.h"
#include "Food.h"
#include "ScoreManager.h"

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};


class GameStateManager {
public:
	
	void setState(GameState newState);
	GameState getState() const;
private:
	GameState currentState = GameState::MENU;
};


class GameConfig {
public:
	static constexpr int WINDOW_WIDTH = 40;
	static constexpr int WINDOW_HEIGHT = 20;
	static constexpr char SNAKE_HEAD = '0';
	static constexpr char SNAKE_BODY = 'o';
	static constexpr char FOOD_SYMBOL = '*';
	static constexpr char WALL_SYMBOL = '#';
};

class GameInit {
public:
	GameInit();

	void displayGame();
	void getUserInput();
	void upDateGame();
	void growSnake();
	bool isGameOver();
	void updateSnake();
	void drawSnake();
	void startGame();
	void resetGame();
	void snakeSleep();
	void increaseSnakeSpeed();
	void getUserName();
	void showLose();

private:
	Grid grid;
	int snakeSpeed;
	Snake snake;
	Food food;
	Direction userInput;
	string userName;
	GameScores scores;
};







#endif // !GAME_ENGINE_H
