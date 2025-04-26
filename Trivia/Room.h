#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"


typedef struct RoomData 
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	//RoomStatus status; 
	//idk what they meant by this so i did this 
	unsigned int status;
}RoomData;
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