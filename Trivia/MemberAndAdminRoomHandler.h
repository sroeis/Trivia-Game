#pragma once
// Forward declaration
class RequestHandlerFactory;
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class MemberAndAdminRoomHandler : public IRequestHandler
{
protected:
	Room& m_room;
	LoggedUser& m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	const RequestResult getRoomState(const RequestInfo& ri);
	

public:
	MemberAndAdminRoomHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user, Room& room)
		: m_handlerFactory(handlerFactory), m_user(user), m_room(room), m_roomManager(handlerFactory.getRoomManager()) {}
	
	
};