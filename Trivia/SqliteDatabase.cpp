#include "SqliteDatabase.h"
#include <io.h>


SqliteDatabase::SqliteDatabase()
	: _db(nullptr)
{
}

bool SqliteDatabase::open()
{
	string dbPath = DB_PATH;
	int fileExists = _access(dbPath.c_str(), 0);
	int res = sqlite3_open(dbPath.c_str(), &_db);
	if (res != SQLITE_OK)
	{
		std::cerr << "Error opening database: " << sqlite3_errmsg(_db) << std::endl;
		return false;
	}

	const char* sqlStatement = "CREATE TABLE IF NOT EXISTS Users ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Username TEXT NOT NULL UNIQUE, "
		"Password TEXT NOT NULL, "
		"Email TEXT NOT NULL);";
	char* errMsg = nullptr;
	res = sqlite3_exec(_db, sqlStatement, nullptr, nullptr, &errMsg);

	return true;
}

bool SqliteDatabase::close()
{
    sqlite3_close(_db);
	_db = nullptr;
}


bool SqliteDatabase::DoesUserExist(const std::string& username)
{
    string sqlStatement = "SELECT COUNT(*) FROM Users WHERE Username = '" + username + "';";
    int count = 0;
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), callback, &count, &errMsg);
    
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing query: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return count > 0;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
    string sqlStatement = "SELECT COUNT(*) FROM Users WHERE Username = '" + username + "' AND Password = '" + password + "';";
    int count = 0;
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), callback, &count, &errMsg);
    
    if (res != SQLITE_OK)
    {
        std::cerr << "Error executing query: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return count > 0;
}

bool SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
    // First check if user already exists
    if (DoesUserExist(username))
    {
        std::cerr << "User already exists" << std::endl;
        return false;
    }

    string sqlStatement = "INSERT INTO Users (Username, Password, Email) VALUES ('" + 
                         username + "', '" + password + "', '" + email + "');";
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK)
    {
        std::cerr << "Error adding new user: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

int SqliteDatabase::callback(void* data, int argc, char** argv, char** azColName)
{
    int* count = static_cast<int*>(data);
    if (argc > 0 && argv[0]) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

