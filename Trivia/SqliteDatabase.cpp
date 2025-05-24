#include "SqliteDatabase.h"
#include <io.h>
#include <algorithm>
using std::exception;

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

	// Create Statistics table
	const char* statisticsTableSql = "CREATE TABLE IF NOT EXISTS Statistics ("
		"UserID INTEGER PRIMARY KEY, "
		"AvgAnswerTime REAL, "
		"CorrectAnswers INTEGER, "
		"TotalAnswers INTEGER, "
		"GamesPlayed INTEGER, "
		"FOREIGN KEY(UserID) REFERENCES Users(ID));";
	res = sqlite3_exec(_db, statisticsTableSql, nullptr, nullptr, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error creating Statistics table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

	// Create HighScores table
	const char* highScoresTableSql = "CREATE TABLE IF NOT EXISTS HighScores ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"UserID INTEGER UNIQUE, "
		"Score INTEGER, "
		"FOREIGN KEY(UserID) REFERENCES Users(ID));";
	res = sqlite3_exec(_db, highScoresTableSql, nullptr, nullptr, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error creating HighScores table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

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
    
    if (res != SQLITE_OK || count == 0)
    {
        throw exception("User wasn't found");
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
    
    if (res != SQLITE_OK || count == 0)
    {
        sqlite3_free(errMsg);
		throw exception("Error checking password match");
    }

    return count > 0;
}

bool SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
    // First check if user already exists
    if (DoesUserExist(username))
    {
        throw exception("User already exists");
        return false;
    }

    string sqlStatement = "INSERT INTO Users (Username, Password, Email) VALUES ('" + 
                         username + "', '" + password + "', '" + email + "');";
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK)
    {
        sqlite3_free(errMsg);
        throw exception("Error adding new user");
    }

    return true;
}

void SqliteDatabase::CreateQuestionTable()
{
	string sqlStatement = "CREATE TABLE IF NOT EXISTS Questions("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," //argv [0]
		    "Question TEXT NOT NULL," // argv [1]
		    "OptionA TEXT NOT NULL," // argv [2]
            "OptionB TEXT NOT NULL," // argv [3]
            "OptionC TEXT NOT NULL," // argv[4]
            "OptionD TEXT NOT NULL," // argv[5]
            "CorrectOption INTEGER NOT NULL);"; // argv[6]

	char* errMsg = nullptr;
	int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);

	if (res != SQLITE_OK)
	{
		std::cerr << "Error creating Questions table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

void SqliteDatabase::insertQuestion(const std::string& question, const std::string& answer1, const std::string& answer2, const std::string& answer3, const std::string& answer4, const int& correctAnswer)
{
    // correctAnswer should be 1, 2, 3, or 4
    string sqlStatement = "INSERT INTO Questions (Question, OptionA, OptionB, OptionC, OptionD, CorrectOption) VALUES ('" +
        question + "', '" + answer1 + "', '" + answer2 + "', '" + answer3 + "', '" + answer4 + "', " + std::to_string(correctAnswer) + ");";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);

    if (res != SQLITE_OK)
    {
        std::cerr << "Error adding new question: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

const list<Question> SqliteDatabase::getQuestions(const int count) const
{
    std::list<Question> questions;
    struct QuestionsHolder { std::list<Question>* list; } holder{&questions};

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc >= 7) {
            std::string questionText = argv[1] ? argv[1] : "";
            std::vector<std::string> possibleAnswers = {
                argv[2] ? argv[2] : "",
                argv[3] ? argv[3] : "",
                argv[4] ? argv[4] : "",
                argv[5] ? argv[5] : ""
            };
            unsigned int correctIndex = 0;
            if (argv[6]) {
                int dbIndex = std::stoi(argv[6]);
                if (dbIndex >= 1 && dbIndex <= 4)
                    correctIndex = dbIndex - 1;
            }
            Question q(questionText, possibleAnswers, correctIndex);
            static_cast<QuestionsHolder*>(data)->list->push_back(q);
        }
        return 0;
    };

    std::string sql = "SELECT * FROM Questions LIMIT " + std::to_string(count) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &holder, &errMsg);
    if (errMsg) sqlite3_free(errMsg);

    return questions;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const string& username) const
{
    float avgTime = 0.0f;
    int userId = getUserIdByUsername(username);
   
    struct FloatHolder { float value = 0.0f; } holder;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            static_cast<FloatHolder*>(data)->value = std::stof(argv[0]);
        return 0;
    };
    std::string sql = "SELECT AvgAnswerTime FROM Statistics WHERE UserID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &holder, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return holder.value;
}

int SqliteDatabase::getNumOfCorrectAnswers(const string& username) const
{
    int correct = 0;
    int userId = getUserIdByUsername(username);
    if (userId == -1) return 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT CorrectAnswers FROM Statistics WHERE UserID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &correct, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return correct;
}

int SqliteDatabase::getNumOfTotalAnswers(const string& username) const
{
    int total = 0;
    int userId = getUserIdByUsername(username);
    if (userId == -1) return 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT TotalAnswers FROM Statistics WHERE UserID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &total, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return total;
}

int SqliteDatabase::getNumOfPlayerGames(const string& username) const
{
    int games = 0;
    int userId = getUserIdByUsername(username);
    if (userId == -1) return 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT GamesPlayed FROM Statistics WHERE UserID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &games, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return games;
}

int SqliteDatabase::getPlayerScore(const string& username) const
{
    int correct = getNumOfCorrectAnswers(username);
    int total = getNumOfTotalAnswers(username);
    int games = getNumOfPlayerGames(username);
    double avgTime = getPlayerAverageAnswerTime(username);

    double accuracy = total > 0 ? (double)correct / total : 0;
    double accuracyMultiplier = 1.0 + (accuracy * 0.5); // bonus for higher accuracy

    int basePoints = 100;
    int timePenalty = 2;

    int score = (correct * basePoints) * accuracyMultiplier - (avgTime * timePenalty);
    score = std::max(score, 0); // prevent negative score

    return score;
}

const vector<string> SqliteDatabase::getHighScores() const
{
    std::vector<std::string> topUsers;
    struct UserScoreHolder { std::vector<std::string>* vec; } holder{&topUsers};
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 1 && argv[0] && argv[1]) {
            std::string entry = std::string(argv[0]) + ": " + argv[1];
            static_cast<UserScoreHolder*>(data)->vec->push_back(entry);
        }
        return 0;
    };
    std::string sql = "SELECT Users.Username, HighScores.Score FROM HighScores JOIN Users ON HighScores.UserID = Users.ID ORDER BY HighScores.Score DESC LIMIT 5;";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &holder, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return topUsers;
}

int SqliteDatabase::callback(void* data, int argc, char** argv, char** azColName)
{
    int* count = static_cast<int*>(data);
    if (argc > 0 && argv[0]) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

int SqliteDatabase::getUserIdByUsername(const std::string& username) const
{
    int userId = -1;
    std::string sql = "SELECT ID FROM Users WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), userIdCallback, &userId, &errMsg);
    if (res != SQLITE_OK) {
       // std::cerr << "Error getting user ID: " << (errMsg ? errMsg : "") << std::endl;
        if (errMsg) sqlite3_free(errMsg);
		//throw std::out_of_range("Error getting userID");
        return -1;
    }
    return userId;
}

int SqliteDatabase::userIdCallback(void* data, int argc, char** argv, char** azColName) {
    if (argc > 0 && argv[0]) {
        int* idPtr = static_cast<int*>(data);
        *idPtr = std::stoi(argv[0]);
    }
    return 0;
}

