#pragma once
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory;

class MemberAndAdminRoomHandler : public IRequestHandler
{
protected:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
	const RequestResult getRoomState(const RequestInfo& ri);



public:
	MemberAndAdminRoomHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);
	
};