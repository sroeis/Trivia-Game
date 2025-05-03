#include "RoomManager.h"

void RoomManager::CreateRoom(const LoggedUser& user, const RoomData& roomData)
{
	Room room(roomData, user);
	m_rooms.insert(std::make_pair(roomData.id, room));
}

void RoomManager::deleteRoom(const int& ID)
{
	auto it = m_rooms.find(ID);
	if (it != m_rooms.end())
	{
		m_rooms.erase(it);
	}
	else
	{
		//throw an error later?
	}

}

unsigned int RoomManager::getRoomState(const int& ID) const 
{
	return m_rooms.at(ID).getRoomData().status;//i think idk what they want or what status is really supposed to be.
}

std::vector<Room> RoomManager::getRooms() const
{
	std::vector<Room> allRooms;

	for (auto it : this->m_rooms)
	{
		allRooms.push_back(it.second);
	}
	return allRooms;

}

Room& RoomManager::getRoom(const int& ID) 
{
	return m_rooms.at(ID);
}
