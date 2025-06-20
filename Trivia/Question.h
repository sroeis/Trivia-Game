#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class Question
{
public:
	Question(const string& question, const vector<string>& possibleAnswers, unsigned int correctAnswer)
		: m_question(question), m_possibleAnswers(possibleAnswers), m_correctAnswer(correctAnswer) {}
	Question() { m_correctAnswer = 0; m_question = ""; }
	string getQuestion() const { return m_question; }
	vector<string> getPossibleAnswers() const { return m_possibleAnswers; }
	int getCorrectAnswerId() const { return m_correctAnswer; }
private:
	string m_question;
	unsigned int m_correctAnswer;
	vector<string> m_possibleAnswers;
};
