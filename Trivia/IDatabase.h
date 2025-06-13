#pragma once
#include <string>
#include "sqlite3.h"
#include <list>
#include "Question.h"
#include <vector>

using std::list;
using std::string;
using std::vector;

class IDataBase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool DoesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual bool addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual void CreateQuestionTable() = 0;
	virtual void insertQuestion(const std::string& question, const std::string& answer1, const std::string& answer2, const std::string& answer3, const std::string& answer4, const int& correctAnswer) = 0;

	virtual const vector<Question> getQuestions(const int count) const = 0;
	virtual float getPlayerAverageAnswerTime(const string& username) const = 0;
	virtual int getNumOfCorrectAnswers(const string& username) const = 0;
	virtual int getNumOfTotalAnswers(const string& username) const = 0;
	virtual int getNumOfPlayerGames(const string& username) const = 0;
	virtual int getPlayerScore(const string& username) const = 0;
	virtual const vector<string> getHighScores() const = 0;
};