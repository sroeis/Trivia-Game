#pragma once
#include <string>

using std::string;

class LoggedUser
{
private:
	string m_username;
public:
	LoggedUser(string username) : m_username(username) {}
	string getUsername() const { return m_username; }

	bool operator<(const LoggedUser& other) const {
		return m_username < other.m_username;
	}
};
