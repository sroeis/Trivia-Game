#pragma once
#include <string>

using std::string;

struct PlayerResults {
    string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
};
