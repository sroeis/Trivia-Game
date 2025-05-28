#include "LoginManager.h"
#include <iostream>

using std::exception;

SignUpStatus LoginManager::signup(const string username, const string password, const string email)
{
	if (m_dataBase->addNewUser(username, password, email))
	{
		LoggedUser newUser(username);
		m_loggedUsers.push_back(newUser);
		return true; // Sign up successful
	}
	else
	{
		return false; // Sign up failed
	}
}

LoginStatus LoginManager::login(const string username, const string password)
{
	std::cout << "login called with username: " << username << " and password: " << password << std::endl;
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it) {
		if (it->getUsername() == username) {
			throw exception("User already logged in");
		}
	}

	if ((m_dataBase->DoesUserExist(username)) && m_dataBase->doesPasswordMatch(username, password))
	{
		LoggedUser newUser(username);
		m_loggedUsers.push_back(newUser);
		return true; // Login successful
	}

	return false; // Login failed
}

void LoginManager::logout(const string username)
{
	// Find the user in the loggedUsers vector and remove them
	auto it = std::remove_if
	(m_loggedUsers.begin(), m_loggedUsers.end(),
		[&username](const LoggedUser& user)
		{
			return user.getUsername() == username;
		}
	);
	m_loggedUsers.erase(it, m_loggedUsers.end());
}