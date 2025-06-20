#pragma once

#include <vector>
#include <map>
#include "GameData.h"
#include "LoggedUser.h"
#include "PlayerResults.h"
#include "SqliteDataBase.h"

using std::vector;
using std::map;

class Game
{
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	IDataBase* m_database;
	unsigned int m_gameId;
	unsigned int m_numberOfPlayersThatGotResults;
	void submitGameStatsToDB(const LoggedUser& user);

public:
	~Game();
	Game(unsigned int gameId, const vector<Question> questions, const vector<LoggedUser>& players, IDataBase* db);
	const vector<PlayerResults> getPlayersResults();
	const int submitAnswer(const unsigned int answerId, const unsigned int timeTaken, const LoggedUser& user);
	const bool isPlayerInGame(const LoggedUser& player) const;
	const unsigned int getGameId() const { return m_gameId; }
	const Question& getQuestionForUser(const LoggedUser& user) const;
	void removePlayer(const LoggedUser& player);
	void removeAllPlayers();
	bool IsGameEmpty();
	bool didAllGotResults() const;

	map<LoggedUser, GameData>& getPlayers() { return m_players; }
};