#include "Game.h"
//need to add Timer!!!!
void Game::submitGameStatsToDB(const GameData& gameData)
{
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

bool Game::submitAnswer(const unsigned int answerId, const LoggedUser& user)
{
	GameData& gameData = m_players[user];
	bool isCorrect = gameData.currentQuestion.getCorrectAnswerId() == answerId;

	if (isCorrect)
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
		submitGameStatsToDB(gameData);
		removePlayer(user);
		return true; // Game finished
	}
	return isCorrect;
}

void Game::removePlayer(const LoggedUser& player)
{
	m_players.erase(player);
}

void Game::removeAllPlayers()
{
	m_players.clear();
}

