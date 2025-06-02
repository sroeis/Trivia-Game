#pragma once
#include "MemberAndAdminRoomHandler.h"
class RoomMemberRequestHandler : public MemberAndAdminRoomHandler
{
private:
	const RequestResult leaveRoom(const RequestInfo& ri);

public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user, Room& room)
		: MemberAndAdminRoomHandler(handlerFactory, user, room) {}
	bool isRequestRelevant(const RequestInfo& request) override;
	const RequestResult handleRequest(const RequestInfo& request) override;
};

