#pragma once

#include <iostream>
#include <map>
#include "Room.h"

class RoomManager 
{
public:
	void CreateRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(const int& ID);
	unsigned int getRoomState(const int& ID) const;
	std::vector<Room> getRooms() const;
	Room& getRoom(const int& ID);

private:
	std::map<unsigned int, Room> m_rooms;

};