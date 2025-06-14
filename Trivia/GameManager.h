#pragma once
#include "Game.h"
#include <vector>
#include "SqliteDatabase.h"


using std::vector;

class GameManager
{
	IDataBase* m_database;
	vector<Game> m_games;
	static unsigned int gameIdCounter;
public:
	GameManager(IDataBase* database) : m_database(database) {}
	Game& getGame(const LoggedUser& user);
	Game createGame(const vector<LoggedUser>& playersInRoom);
	void deleteGame(unsigned int gameId);
};