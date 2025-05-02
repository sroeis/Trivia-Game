#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"

class Room 
{
public:
	Room() = default;
	Room(const RoomData& metadata,const LoggedUser& user);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();

	RoomData getRoomData();


private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};