#include "GameManager.h"
#define NUMBER_OF_QUESTIONS 10


unsigned int GameManager::gameIdCounter = 0;

Game GameManager::createGame(const vector<LoggedUser>& playersInRoom)
{
	return Game(gameIdCounter++, m_database->getQuestions(NUMBER_OF_QUESTIONS), playersInRoom);
}

void GameManager::deleteGame(unsigned int gameId)
{
	m_games.erase(
		std::remove_if(m_games.begin(), m_games.end(),
			[gameId](const Game& game) {
				return game.getGameId() == gameId;
			}),
		m_games.end()
	);
}
	//m_games[gameId].removeAllPlayers();
	
