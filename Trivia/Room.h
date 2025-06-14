#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"

using std::vector;
using std::string;
class Room 
{
public:
	Room() = default;
	Room(const RoomData& metadata,const LoggedUser& user);
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	const vector<string> getAllUsers() const;
	const vector<LoggedUser>& getLoggedUsers() const { return m_users; };
	const RoomData& getRoomData() const;
	void switchRoomState();

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};