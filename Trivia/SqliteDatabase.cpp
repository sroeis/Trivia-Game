#include "SqliteDatabase.h"
#include <io.h>
#include <algorithm>
#include "Questions.h"
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
		"Username TEXT PRIMARY KEY, "
		"Password TEXT NOT NULL, "
		"Email TEXT NOT NULL);";
	char* errMsg = nullptr;
	res = sqlite3_exec(_db, sqlStatement, nullptr, nullptr, &errMsg);

	// Create Statistics table
	const char* statisticsTableSql = "CREATE TABLE IF NOT EXISTS Statistics ("
		"Username TEXT PRIMARY KEY, "
		"AvgAnswerTime REAL, "
		"CorrectAnswers INTEGER, "
		"TotalAnswers INTEGER, "
		"GamesPlayed INTEGER, "
		"Score INTEGER DEFAULT 0, "
		"FOREIGN KEY(Username) REFERENCES Users(Username));";
	res = sqlite3_exec(_db, statisticsTableSql, nullptr, nullptr, &errMsg);
	if (res != SQLITE_OK) {
		std::cerr << "Error creating Statistics table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}

	CreateQuestionTable();
	Questions::getQuestions(30, "Any", "easy", *this);
	

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
	std::cout << "Checking if user exists: " << username << std::endl;
    string sqlStatement = "SELECT COUNT(*) FROM Users WHERE Username = '" + username + "';";
    int count = 0;
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sqlStatement.c_str(), callback, &count, &errMsg);
	std::cout << "SQL Result: " << res << ", Count: " << count << std::endl;
    
    
    if (res != SQLITE_OK || count == 0)
    {
        sqlite3_free(errMsg);
        throw exception("User doesn't exist.");
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
		throw exception("Password is incorrect");
    }

    return count > 0;
}

bool SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
	std::cout << "Adding new user: " << username << std::endl;
    // First check if user already exists
    try
    {
        DoesUserExist(username);
        throw exception("User already exists");
        return false;
    }
    catch(const exception e)
    {
        string sqlStatement = "INSERT INTO Users (Username, Password, Email) VALUES ('" +
            username + "', '" + password + "', '" + email + "');";

        char* errMsg = nullptr;
        int res = sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, &errMsg);

        if (res != SQLITE_OK)
        {
            sqlite3_free(errMsg);
            throw exception("Error adding new user");
        }
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

int SqliteDatabase::submitGameStatistics(const string& username, const GameData& data)
{
    // check if user exists in statistics table
    int gamesPlayed = getNumOfPlayerGames(username);
    
    if (gamesPlayed == 0) 
    {
        // Calculate score for new user
        double accuracy = (double)data.correctAnswerCount / (data.correctAnswerCount + data.wrongAnswerCount);
        double accuracyMultiplier = 1.0 + (accuracy * 0.5);
        int basePoints = 100;
        int timePenalty = 2;
        int newScore = (data.correctAnswerCount * basePoints) * accuracyMultiplier - (data.averageAnswerTime * timePenalty);
        newScore = std::max(newScore, 0);

        string insertStatsSql = "INSERT INTO Statistics (Username, AvgAnswerTime, CorrectAnswers, TotalAnswers, GamesPlayed, Score) "
            "VALUES ('" + username + "', " + std::to_string(data.averageAnswerTime) + ", " 
            + std::to_string(data.correctAnswerCount) + ", " 
            + std::to_string(data.correctAnswerCount + data.wrongAnswerCount) + ", 1, " 
            + std::to_string(newScore) + ");";

        char* errMsg = nullptr;
        if (sqlite3_exec(_db, insertStatsSql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error inserting initial statistics: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return -1;
        }
    }
    else 
    {
        float currentAvgTime = getPlayerAverageAnswerTime(username);
        float newAvgTime = ((currentAvgTime * gamesPlayed) + data.averageAnswerTime) / (gamesPlayed + 1);
        
        // Calculate score for this game
        double accuracy = (data.correctAnswerCount + data.wrongAnswerCount) > 0 ? 
            (double)data.correctAnswerCount / (data.correctAnswerCount + data.wrongAnswerCount) : 0;
        double accuracyMultiplier = 1.0 + (accuracy * 0.5);
        int basePoints = 100;
        int timePenalty = 2;
        int gameScore = (data.correctAnswerCount * basePoints) * accuracyMultiplier - (data.averageAnswerTime * timePenalty);
        gameScore = std::max(gameScore, 0);
        
        string updateStatsSql = "UPDATE Statistics SET "
            "AvgAnswerTime = " + std::to_string(newAvgTime) + ", "
            "CorrectAnswers = CorrectAnswers + " + std::to_string(data.correctAnswerCount) + ", "
            "TotalAnswers = TotalAnswers + " + std::to_string(data.correctAnswerCount + data.wrongAnswerCount) + ", "
            "GamesPlayed = GamesPlayed + 1, "
            "Score = Score + " + std::to_string(gameScore) + " "
            "WHERE Username = '" + username + "';";

        char* errMsg = nullptr;
        if (sqlite3_exec(_db, updateStatsSql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Error updating statistics: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return -1;
        }
    }

    return 1;
}

const vector<Question> SqliteDatabase::getQuestions(const int count) const
{
    std::vector<Question> questions;
    struct QuestionsHolder { std::vector<Question>* vec; } holder{&questions};

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
            static_cast<QuestionsHolder*>(data)->vec->push_back(q);
        }
        return 0;
    };

    std::string sql = "SELECT * FROM Questions ORDER BY RANDOM() LIMIT " + std::to_string(count) + ";";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &holder, &errMsg);
    if (errMsg) sqlite3_free(errMsg);

    return questions;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const string& username) const
{
    float avgTime = 0.0f;
   
    struct FloatHolder { float value = 0.0f; } holder;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            static_cast<FloatHolder*>(data)->value = std::stof(argv[0]);
        return 0;
    };
    std::string sql = "SELECT AvgAnswerTime FROM Statistics WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &holder, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return holder.value;
}

int SqliteDatabase::getNumOfCorrectAnswers(const string& username) const
{
    int correct = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT CorrectAnswers FROM Statistics WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &correct, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return correct;
}

int SqliteDatabase::getNumOfTotalAnswers(const string& username) const
{
    int total = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT TotalAnswers FROM Statistics WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &total, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return total;
}

int SqliteDatabase::getNumOfPlayerGames(const string& username) const
{
    int games = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT GamesPlayed FROM Statistics WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &games, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
    return games;
}

int SqliteDatabase::getPlayerScore(const string& username) const
{
    int score = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0])
            *static_cast<int*>(data) = std::stoi(argv[0]);
        return 0;
    };
    std::string sql = "SELECT Score FROM Statistics WHERE Username = '" + username + "';";
    char* errMsg = nullptr;
    sqlite3_exec(_db, sql.c_str(), callback, &score, &errMsg);
    if (errMsg) sqlite3_free(errMsg);
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
    std::string sql = "SELECT Username, Score FROM Statistics ORDER BY Score DESC LIMIT 5;";
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

