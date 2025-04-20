#pragma once
#include <string>
class IDataBase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool DoesUserExist(const std::string& username) = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	virtual bool addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;
};