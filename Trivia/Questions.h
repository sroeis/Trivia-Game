#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include "json.hpp"
#include "SqliteDatabase.h"

// URl_1 + num of questions + URL_2 + category + URL_3 + difficulty + URL_4
#define URL_1 "https://opentdb.com/api.php?amount="
#define URL_2 "&category="
#define URL_3 "&difficulty="
#define URL_4 "&type=multiple"

class Questions 
{
public:
    static void getQuestions(int numOfQuestions, const std::string& category, const std::string& difficulty, SqliteDatabase & db);

private:
    static const std::string& buildUrl(int numOfQuestions, const std::string& category, const std::string& difficulty);
    static std::unordered_map<std::string, int> categoryMap;
    static const std::string& getResponse(const std::string& url);
};