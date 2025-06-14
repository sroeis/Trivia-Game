#pragma once
#include "Game.h"
#include "Room.h"
#include <vector>
#include "SqliteDatabase.h"


using std::vector;

class GameManager
{
	IDataBase* m_database;
	vector<Game> m_games;
	
public:
	GameManager(IDataBase* database) : m_database(database) {}
	Game& getGame(const LoggedUser& user);
	Game createGame(Room& room);
	void deleteGame(unsigned int gameId);
};