#pragma once
#include "IDatabase.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

class StatisticsManager
{
public:
	StatisticsManager(IDataBase* dataBase) : m_dataBase(dataBase) {}
	vector<string> getHighScore() const;
	vector<string> getUserStatistics(const string& username) const;
private:
	IDataBase* m_dataBase;
};