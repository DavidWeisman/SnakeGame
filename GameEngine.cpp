#include <iostream>
#include "GameEngine.h"
#include <conio.h>
#include <thread>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

bool playing;
void GameStateManager::setState(GameState newState) {
    currentState = newState;
}

GameState GameStateManager::getState() const {
    return currentState;
}

GameInit::GameInit() : 
    grid(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT,GameConfig::WALL_SYMBOL),
    food(GameConfig::FOOD_SYMBOL, GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT) 
{
    snakeSpeed = 150;
}

void GameInit::getUserName() {
    cout << "What is your Name: ";
    cin >> userName;
    while (userName.size() > 9) {
        cout << "Your name has to be less then 10 characters." << endl;
        cout << "What is your Name: ";
        cin >> userName;
    }
}

void playBiteSound(string fileName) {
    std::wstring LwideFileName(fileName.begin(), fileName.end());

    PlaySound(TEXT(wideFileName.c_str()), NULL, SND_FILENAME | SND_ASYNC);
}


void GameInit::showLose() {
    cout << R"(                                
                   (                 
 (            (    )\            (   
 )\ )   (    ))\  ((_) (   (    ))\  
(()/(   )\  /((_)  _   )\  )\  /((_) 
 )(_)) ((_)(_))(  | | ((_)((_)(_))   
| || |/ _ \| || | | |/ _ \(_-</ -_)  
 \_, |\___/ \_,_| |_|\___//__/\___|  
 |__/     
                           
)" << endl;
    
    int currntScore = scores.getCurrntScore();
    int bestScore = scores.getPlayerByname(userName).score;


    if (currntScore == bestScore) {
        cout << "WELL DONE, YOU BROKE YOUR PREVIOUS RECORD!!!" << endl;
        cout << "YOUR NEW RECORD IS: " << currntScore << endl;
    }
    else {
        cout << "YOUR SCORE IS: " << currntScore << endl;
        cout << "YOUR BEST SCORE IS: " << bestScore << endl;
    }
    
    cout << "\n";

    int index = scores.getIndexbyname(userName);
    index++;

    if (index <= 3) {
        cout << "YOU ARE IN THE TOP 3!!!!" << endl; 
        playBiteSound("winningSound.wav");        
    }
    cout << "YOU ARE IN " << index << " PLACE!!\n" << endl;
    
    scores.saveScores();
}






void GameInit::snakeSleep() {
    this_thread::sleep_for(chrono::milliseconds(snakeSpeed));
}

void GameInit::increaseSnakeSpeed() {
    snakeSpeed -= 20;
}


void GameInit::resetGame() {
    snake.resetSanke();
    food.spawn();
    snakeSpeed = 200;
}

void GameInit::startGame() {
    grid.render();

   
    scores.loadScores();
    if (!scores.checkIfPlayerExist(userName)) {
        UserAndScore newUser;
        newUser.name = userName;
        newUser.score = 0;
        scores.addPlayer(newUser);
    }
    scores.loadTableRecords();
    scores.loadUsersScores(userName);

    playing = true;
    thread t2(&GameInit::getUserInput, this);
    t2.detach();
    displayGame();
    
    
}

void GameInit::displayGame() {
    drawSnake();
    food.drawFood();
}

void GameInit::upDateGame() {
    snake.SetDirection(userInput);
    updateSnake();
    growSnake();
    snake.move();
}

void GameInit::growSnake() {
    if (snake.get_head().x == food.getFoodCoordinates().x && snake.get_head().y == food.getFoodCoordinates().y) {
        snake.grow();
        food.spawn();
        increaseSnakeSpeed();
        playBiteSound("biteSound3.wav");
        scores.loadUsersScores(userName);
    }

}

bool comperCoordinates(Coordinate first, Coordinate second) {
    return (first.x == second.x && first.y == second.y);
}

void drawSimbole(Coordinate coordinate, char simbol) {
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    int previusX = csbi.dwCursorPosition.X;
    int previusY = csbi.dwCursorPosition.Y;


    csbi.dwCursorPosition.X = coordinate.x;
    csbi.dwCursorPosition.Y = coordinate.y;

    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
    SetConsoleTextAttribute(hStdout, 10);
    
    std::cout << simbol;

    SetConsoleTextAttribute(hStdout, 15);

    csbi.dwCursorPosition.X = previusX;
    csbi.dwCursorPosition.Y = previusY;

    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}

void GameInit::updateSnake() {
    if (comperCoordinates(snake.get_head(), snake.get_tail())) {
        drawSimbole(snake.get_head(), ' ');
    }
    else {
        drawSimbole(snake.get_tail(), ' ');
    }
}

void GameInit::drawSnake() {

    drawSimbole(snake.get_head(), GameConfig::SNAKE_HEAD);

    if (!comperCoordinates(snake.get_head(), snake.get_tail())) {
        drawSimbole(snake.get_one_befor_head(), GameConfig::SNAKE_BODY);
    }

}

bool GameInit::isGameOver() {
    int snakeX = snake.get_head().x;
    int snakeY = snake.get_head().y;

    if (snakeX < 1 || snakeX > GameConfig::WINDOW_WIDTH - 2 || snakeY < 1 || snakeY > GameConfig::WINDOW_HEIGHT - 2) {
        playing = false;
        return true;
    }

    if (snake.isSnakeKrash()) {
        playing = false;      
        return true;
    }

    return false;
}

void GameInit::getUserInput() {
    while (playing) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {
                case 72:
                    userInput = UP;
                    break;
                case 80:
                    userInput = DOWN;
                    break;
                case 77:
                    userInput = RIGHT;
                    break;
                case 75:
                    userInput = LEFT;
                    break;
                }
            }
        }
    }
    
}













