#pragma once

#include <vector>
#include <map>
#include "GameData.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

using std::vector;
using std::map;

class Game
{
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	IDataBase* m_database;
	unsigned int m_gameId;
	void submitGameStatsToDB(const GameData& gameData);

public:
	Game(unsigned int gameId, const vector<Question> questions, const vector<LoggedUser>& players);
	const int submitAnswer(const unsigned int answerId, const LoggedUser& user);
	const unsigned int getGameId() const { return m_gameId; }
	const Question& getQuestionForUser(const LoggedUser& user) const;
	void removePlayer(const LoggedUser& player);
	void removeAllPlayers();
};