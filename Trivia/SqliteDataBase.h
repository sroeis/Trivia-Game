#pragma once

#include "IDatabase.h"
#include <string>
#include <iostream>
#define DB_PATH "triviaDB.db"

using std::string;

class SqliteDatabase : public IDataBase
{
public:
	SqliteDatabase();
	bool open() override;
	bool close() override;
	bool DoesUserExist(const std::string& username) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	bool addNewUser(const std::string& username, const std::string& password, const std::string& email) override;
	void CreateQuestionTable();
	void insertQuestion(const std::string& question, const std::string& answer1, const std::string& answer2, const std::string& answer3, const std::string& answer4, int correctAnswer);
	
private:
	sqlite3* _db;
	static int callback(void* data, int argc, char** argv, char** azColName);
};
