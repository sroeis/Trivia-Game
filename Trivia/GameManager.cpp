#include "GameManager.h"
#define NUMBER_OF_QUESTIONS 10


unsigned int GameManager::gameIdCounter = 0;

Game GameManager::createGame(const vector<LoggedUser>& playersInRoom)
{
	return Game(gameIdCounter++, m_database->getQuestions(NUMBER_OF_QUESTIONS), playersInRoom);
}

void GameManager::deleteGame(unsigned int gameId)
{
	m_games[gameId].removeAllPlayers();
	m_games.erase(m_games.begin() + gameId);
}
