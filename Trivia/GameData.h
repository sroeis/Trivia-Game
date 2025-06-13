#pragma once
#include "Question.h"

struct GameData {
	Question currentQuestion;
	unsigned int currentQuestionIndex;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};
