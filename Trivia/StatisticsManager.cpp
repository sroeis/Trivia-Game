#include "StatisticsManager.h"

vector<string> StatisticsManager::getHighScore()
{
    return this->m_dataBase->getHighScores();
}

vector<string> StatisticsManager::getUserStatistics(const string& username)
{
	vector<string> userStatistics;
	float avgTime = m_dataBase->getPlayerAverageAnswerTime(username);
	int correct = m_dataBase->getNumOfCorrectAnswers(username);
	int total = m_dataBase->getNumOfTotalAnswers(username);
	int games = m_dataBase->getNumOfPlayerGames(username);
	int score = m_dataBase->getPlayerScore(username);

	userStatistics.push_back("Average Answer Time: " + std::to_string(avgTime));
	userStatistics.push_back("Correct Answers: " + std::to_string(correct));
	userStatistics.push_back("Total Answers: " + std::to_string(total));
	userStatistics.push_back("Games Played: " + std::to_string(games));
	userStatistics.push_back("Score: " + std::to_string(score));

	return userStatistics;
}
