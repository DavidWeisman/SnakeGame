#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <vector>

typedef struct UserAndScore {
	std::string name;
	int score;
};


class GameScores {
public:
	void loadScores();
	void addPlayer(UserAndScore user);
	void saveScores();
	UserAndScore getPlayerByname(std::string playerName);
	bool checkIfPlayerExist(std::string playerName);
	void loadTableRecords();
	void loadUsersScores(std::string user);
	int getIndexbyname(std::string name);
	void bubbleSort();
	int getCurrntScore();
private:
	std::vector<UserAndScore> scores;
};














#endif // !SCORE_MANAGER_H
