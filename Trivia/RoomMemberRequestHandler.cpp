#include "RoomMemberRequestHandler.h"

const RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& ri)
{
	RequestResult result;
	
    try
    {
		m_roomManager.getRoom(m_room.getRoomData().id).removeUser(m_user);
		result.response = JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse{ STATUS_OK });
		result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);

    }
	catch (const std::exception& e)
	{
		ErrorResponse response;
		response.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = this;
	}
	return result;
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& request)
{
	return request.id == LEAVE_ROOM_CODE || request.id == GET_ROOM_STATE_CODE;
}

const RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& request)
{
	switch (request.id)
	{
	case LEAVE_ROOM_CODE:
		return leaveRoom(request);
	case GET_ROOM_STATE_CODE:
		return getRoomState(request);
	
	}
}
