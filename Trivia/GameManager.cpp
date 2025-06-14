#include "GameManager.h"


Game& GameManager::getGame(const LoggedUser& user)
{
	for(auto& game : m_games ) {
		if (game.isPlayerInGame(user)) {
			return game;
		}
	}
}

Game GameManager::createGame(Room& room)
{
	return Game(room.getRoomData().id, m_database->getQuestions(room.getRoomData().numOfQuestionsInGame <= 30 ? room.getRoomData().numOfQuestionsInGame : 30), room.getLoggedUsers());
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
	
