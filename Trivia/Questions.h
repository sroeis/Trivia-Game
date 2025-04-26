#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include "curl/curl.h"
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
    static void getQuestions(int numOfQuestions, std::string category,std::string difficulty, SqliteDatabase db);

private:
    static std::string buildUrl(int numOfQuestions, std::string category, std::string difficulty);
    static std::ostringstream getResponse(std::string url);
    static std::unordered_map<std::string, int> categoryMap;

};