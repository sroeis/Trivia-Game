#pragma once

#include "IDatabase.h"
#include <string>
#include <iostream>
#define DB_PATH "triviaDB"

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
	
private:
	sqlite3* _db;
	static int callback(void* data, int argc, char** argv, char** azColName);
};
