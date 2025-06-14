#pragma once

#include "IDatabase.h"
#include <string>
#include <iostream>
#include <vector>
#include "Question.h"
#define DB_PATH "triviaDB.db"

using std::string;
using std::vector;

class SqliteDatabase : public IDataBase
{
public:
	SqliteDatabase();
	bool open() override;
	bool close() override;
	bool DoesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	bool addNewUser(const std::string& username, const std::string& password, const std::string& email) override;
	void CreateQuestionTable() override;
	void insertQuestion(const std::string& question, const std::string& answer1, const std::string& answer2, const std::string& answer3, const std::string& answer4, const int& correctAnswer) override;
	int submitGameStatistics(const string& username, const GameData& data) override;
	

	const vector<Question> getQuestions(const int count) const override;
	float getPlayerAverageAnswerTime(const string& username) const override;
	int getNumOfCorrectAnswers(const string& username) const override;
	int getNumOfTotalAnswers(const string& username) const override;
	int getNumOfPlayerGames(const string& username) const override;
	int getPlayerScore(const string& username) const override;
	const vector<string> getHighScores() const override;
	
private:
	sqlite3* _db;
	static int callback(void* data, int argc, char** argv, char** azColName);
	int getUserIdByUsername(const std::string& username) const;
	static int userIdCallback(void* data, int argc, char** argv, char** azColName);
};
