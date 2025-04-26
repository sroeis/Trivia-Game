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
    int res = sqlite3_close(_db);
    _db = nullptr;
    return res == SQLITE_OK;
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

void SqliteDatabase::CreateQuestionTable()
{
	string sqlStatement = "CREATE TABLE IF NOT EXISTS Questions("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "Question TEXT NOT NULL,"
            "OptionA TEXT NOT NULL,"
            "OptionB TEXT NOT NULL,"
            "OptionC TEXT NOT NULL,"
            "OptionD TEXT NOT NULL,"
            "CorrectOption CHAR(1) NOT NULL);" ;//like 'A', 'B', 'C', or 'D'

	char* errMsg = nullptr;
	int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);

	if (res != SQLITE_OK)
	{
		std::cerr << "Error creating Questions table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

void SqliteDatabase::insertQuestion(const std::string& question, const std::string& answer1, const std::string& answer2, const std::string& answer3, const std::string& answer4, int correctAnswer)
{
    char ans = ' ';
    switch (correctAnswer)
    {
	case 1:
        ans = 'A';
		break;
	case 2:
        ans = 'B';
		break;
	case 3:
        ans = 'C';
		break;
	case 4:
        ans = 'D';
		break;
    default:
        break;
    }

	string sqlStatement = "INSERT INTO Questions (Question, OptionA, OptionB, OptionC, OptionD, CorrectOption) VALUES ('" +
		question + "', '" + answer1 + "', '" + answer2 + "', '" + answer3 + "', '" + answer4 + "', '" + ans + "');";

	char* errMsg = nullptr;
	int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);

	if (res != SQLITE_OK)
	{
		std::cerr << "Error adding new question: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

}

int SqliteDatabase::callback(void* data, int argc, char** argv, char** azColName)
{
    int* count = static_cast<int*>(data);
    if (argc > 0 && argv[0]) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

