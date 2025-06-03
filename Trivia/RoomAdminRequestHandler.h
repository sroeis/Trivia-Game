#pragma once
#include "MemberAndAdminRoomHandler.h"

class RoomAdminRequestHandler : public MemberAndAdminRoomHandler
{
private:
	const RequestResult closeRoom(const RequestInfo& ri);
	const RequestResult startGame(const RequestInfo& ri);

public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory,const LoggedUser& user,const Room& room)
		: MemberAndAdminRoomHandler(handlerFactory, user, room) {}
	bool isRequestRelevant(const RequestInfo& request) override;
	const RequestResult handleRequest(const RequestInfo& request) override;
	
};
