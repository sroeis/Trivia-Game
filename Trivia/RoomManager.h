#pragma once

#include <iostream>
#include <map>
#include "Room.h"

class RoomManager 
{
public:
	void RemoveUserFromRoom(const LoggedUser& user, int roomId);
	void CreateRoom(const LoggedUser& user, const RoomData& roomData);
	void deleteRoom(const int& ID);
	unsigned int getRoomState(const int& ID) const;
	const std::vector<Room> getRooms() const;
	Room& getRoom(const int& ID);

private:
	std::map<unsigned int, Room> m_rooms;

};