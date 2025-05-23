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
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const std::vector<std::string> getAllUsers() const;

	const RoomData& getRoomData() const;


private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};