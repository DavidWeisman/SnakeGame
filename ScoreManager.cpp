#include <iostream>
#include "ScoreManager.h";
#include "Stringcrypto.h"
#include <fstream>
#include <string>
#include <windows.h>
#include <string>
#include <sstream>

#define FILE_NAME "encrypted_secret.bin"




using namespace std;

int scorecounter;


void parseDecryptedString(const std::string& decrypted, std::string& name, int& score) {
    std::istringstream iss(decrypted);
    std::string scoreStr;

 
    std::getline(iss, name, ' ');

 
    std::getline(iss, scoreStr);

 
    score = static_cast<unsigned char>(scoreStr[0]);;
}


void GameScores::loadScores() {
    scorecounter = -1;

    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        string decryptLine = SecureStringCrypto::decrypt(line);
        UserAndScore user;

        parseDecryptedString(decryptLine, user.name, user.score);      

        scores.push_back(user);
    }
    bubbleSort();
}



void GameScores::bubbleSort()
{
    int n = scores.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (scores[j].score < scores[j + 1].score) {
                swap(scores[j], scores[j + 1]);
            }                
        }
    }
}






void GameScores::addPlayer(UserAndScore user) {
    if (scores.size() == 13) {
        scores.pop_back();
    }
    scores.push_back(user);
}

void GameScores::saveScores() {
    std::ofstream file(FILE_NAME);
    string line;

    for (int i = 0; i < scores.size(); i++) {
        line = "";
        line += scores[i].name;
        line += " ";
        line += scores[i].score;
        file << SecureStringCrypto::encrypt(line);
        file << '\n';
    }
    scores.clear();
}

bool GameScores::checkIfPlayerExist(std::string playerName) {
    for (int i = 0; i < scores.size(); i++) {
        if (strcmp(scores[i].name.c_str(), playerName.c_str()) == 0) {
            return true;
        }
    }
    return false;
}


UserAndScore GameScores::getPlayerByname(std::string playerName) {
    for (int i = 0; i < scores.size(); i++) {
        if (strcmp(scores[i].name.c_str(), playerName.c_str()) == 0) {
            return scores[i];
        }
    }
 
}

void GameScores::loadTableRecords() {
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    csbi.dwCursorPosition.X = 40;
   
    for (int i = 0; i < scores.size(); i++) {
        csbi.dwCursorPosition.Y = 6 + i;
        SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
        cout << "                ";
        SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
        if (strcmp(scores[i].name.c_str(), "Liran") == 0) {
            SetConsoleTextAttribute(hStdout, 13);
            cout << " " << i + 1 << ". " << scores[i].name << " " << scores[i].score;
            SetConsoleTextAttribute(hStdout, 15);
        }
        else {
            cout << " " << i + 1 << ". " << scores[i].name << " " << scores[i].score;
        }
    }
    csbi.dwCursorPosition.Y = 19;
    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);

}

int GameScores::getIndexbyname(string name) {
    for (int i = 0; i < scores.size(); i++) {
        if (strcmp(scores[i].name.c_str(), name.c_str()) == 0) {
            return i;
        }
    }
}


void GameScores::loadUsersScores(string userName) {
    HANDLE hStdout;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        return;
    }

    csbi.dwCursorPosition.X = 53;

    csbi.dwCursorPosition.Y = 1;

    scorecounter++;
    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
    cout << scorecounter;



    csbi.dwCursorPosition.Y = 2;

    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
    if (scorecounter > getPlayerByname(userName).score) {
        cout << scorecounter;
        int index = getIndexbyname(userName);
        scores[index].score++;
        bubbleSort();
        loadTableRecords();
    }
    else {
        cout << getPlayerByname(userName).score;
    }
    

    
    

    csbi.dwCursorPosition.Y = 19;
    SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}



int GameScores::getCurrntScore() {
    return scorecounter;
}