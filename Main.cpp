#include <iostream>
#include "Grid.h";
#include "Snake.h"
#include "Food.h"
#include "GameEngine.h"
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>


void clear() {
    HANDLE hStdout;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = 100;
    scrollRect.Bottom = 30;

    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    ScrollConsoleScreenBuffer(hStdout, &scrollRect, NULL, scrollTarget, &fill);

    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}



void showMenu() {
    cout << R"(                                                                                     
 _ _ _     _                      _          _____         _                            
| | | |___| |___ ___ _____ ___   | |_ ___   |   __|___ ___| |_ ___    ___ ___ _____ ___ 
| | | | -_| |  _| . |     | -_|  |  _| . |  |__   |   | .'| '_| -_|  | . | .'|     | -_|
|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|_|_|__,|_,_|___|  |_  |__,|_|_|_|___|
                                                                     |___|              
           /^\/^\
         _|__|  O|
\/     /~     \_/ \
 \____|__________/  \
        \_______      \
                `\     \                 \
                  |     |                  \
                 /      /                    \
                /     /                       \\
              /      /                         \ \
             /     /                            \  \
           /     /             _----_            \   \
          /     /           _-~      ~-_         |   |
         (      (        _-~    _--_    ~-_     _/   |
          \      ~-____-~    _-~    ~-_    ~-_-~    /
            ~-_           _-~          ~-_       _-~
               ~--______-~                ~-___-~
)" << endl;



    cout << "Press any key to start." << endl;
    _getch();
}


bool playAgain() {
    cout << "Would you like to play again? (y/n): ";
    
    char c;
    while (true) {
        c = _getch();
        if (c == 'y' || c == 'Y') {
            return true;
        }
        else if (c == 'n' || c == 'N') {
            return false;
        }
        else {
            cout << "\nPleas enter a valid answer.";
            cout << "(y/n): ";
        }
    }
}


int main() {
    

    GameStateManager gamestat;
    GameInit game;
     while (gamestat.getState() != GameState::GAME_OVER) {
        if (gamestat.getState() == GameState::MENU) {
            clear();
            game.getUserName();
            clear();
            showMenu();
            clear();
            gamestat.setState(GameState::PLAYING);
            game.startGame();
            
        }
        game.displayGame();
        game.snakeSleep();
        game.upDateGame();
        if (game.isGameOver()) {
            clear();
            game.showLose();
            if (playAgain()) {
                gamestat.setState(GameState::MENU);
                game.resetGame();
            }
            else {
                gamestat.setState(GameState::GAME_OVER);
            }                       
        }
    }
}

