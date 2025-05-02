#pragma once
#include "IDatabase.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

class StatisticsManager
{
public:
	vector<string> getHighScore();
	vector<string> getUserStatistics(const string& username);
private:
	IDataBase* m_dataBase;
};