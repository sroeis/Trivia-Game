#include "Room.h"


Room::Room(const RoomData& metadata, const LoggedUser& user)
	: m_metadata(metadata)
{
	this->addUser(user);
}

void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->getUsername() == user.getUsername())
		{
			m_users.erase(it);
			break;
		}
	}

}

const std::vector<std::string>& Room::getAllUsers() const
{
	std::string str;
	std::vector<std::string> Users;
	for (auto& user : m_users)
	{
		str = user.getUsername();
		Users.push_back(str);
	}
	return Users;
}

const RoomData& Room::getRoomData() const
{
	return m_metadata;
}
