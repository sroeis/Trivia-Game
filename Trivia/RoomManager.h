#pragma once

#include <iostream>
#include <map>
#include "Room.h"

class RoomManager 
{
public:
	void CreateRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<Room> getRooms();

private:
	std::map<unsigned int, Room> m_rooms;
};