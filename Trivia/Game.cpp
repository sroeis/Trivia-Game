#include "Game.h"
//need to add Timer!!!!
using std::exception;

void Game::submitGameStatsToDB(const LoggedUser& user)
{
	m_database->submitGameStatistics(user.getUsername(), m_players[user]);
}

Game::~Game()
{
	m_players.clear();
}

Game::Game(const unsigned int gameId, const vector<Question> questions, const vector<LoggedUser>& players)
	: m_gameId(gameId), m_questions(questions)
{
	for (const auto& player : players)
	{
		m_players[player] = GameData{};
		m_players[player].currentQuestion = m_questions[0]; // Initialize with the first question
	}
}

const vector<PlayerResults> Game::getPlayersResults() const
{
	vector<PlayerResults> results;
	for (const auto& user : m_players)
	{
		PlayerResults res;
		res.username = user.first.getUsername();
		res.correctAnswerCount = user.second.correctAnswerCount;
		res.wrongAnswerCount = user.second.wrongAnswerCount;
		res.averageAnswerTime = user.second.averageAnswerTime;

		results.push_back(res);
	}

	return results;

}

const int Game::submitAnswer(const unsigned int answerId, const LoggedUser& user)
{
	GameData& gameData = m_players[user];
	int correctAnswerId = gameData.currentQuestion.getCorrectAnswerId();

	if (correctAnswerId == answerId)
		gameData.correctAnswerCount++;		
	else
		gameData.wrongAnswerCount++;

	gameData.currentQuestionIndex++;
	if (gameData.currentQuestionIndex < m_questions.size())
	{
		gameData.currentQuestion = m_questions[gameData.currentQuestionIndex];
	}
	else
	{
		gameData.currentQuestion = Question();
		//submitGameStatsToDB(gameData);
		//removePlayer(user);
		//return true; // Game finished
	}
	return correctAnswerId;
}

const bool Game::isPlayerInGame(const LoggedUser& player) const
{
	return m_players.find(player) != m_players.end();
}

const Question& Game::getQuestionForUser(const LoggedUser& user) const
{
	return m_players.at(user).currentQuestion;
}

void Game::removePlayer(const LoggedUser& player)
{
	submitGameStatsToDB(player);
	//m_players.erase(player);
}

void Game::removeAllPlayers()
{
	/*for(const auto& player : m_players)
	{
		submitGameStatsToDB(player.first);
	}*/
	m_players.clear();
}

