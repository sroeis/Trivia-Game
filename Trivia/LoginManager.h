#pragma once
#include <vector>
#include <string>
#include "IDataBase.h"
#include "LoggedUser.h"

using std::vector;
using std::string;

typedef bool SignUpStatus;
typedef bool LoginStatus;

class LoginManager
{
private:
	IDataBase* m_dataBase;
	vector<LoggedUser> m_loggedUsers;
public:
	SignUpStatus signup(const string username, const string password, const string email);
	LoginStatus login(const string username, const string password);
	void logout(const string username);
};
