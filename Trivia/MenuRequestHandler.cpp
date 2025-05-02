#include "MenuRequestHandler.h"
#include "Responses.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == GET_ROOMS_CODE ||
        request.id == GET_PLAYERS_IN_ROOM_CODE ||
        request.id == CREATE_ROOM_CODE ||
        request.id == LOGOUT_CODE ||
        request.id == JOIN_ROOM_CODE ||
        request.id == GET_PERSONAL_STATS_CODE;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request)
{
    switch (request.id)
    {
	case CREATE_ROOM_CODE:
		return createRoom(request);
	case GET_ROOMS_CODE:
	    return getRooms(request);
	case GET_PLAYERS_IN_ROOM_CODE:
		return getPlayersInRoom(request);
	case GET_PERSONAL_STATS_CODE:
		return getPersonalStats(request);
	case LOGOUT_CODE:
		return signout(request);
	case JOIN_ROOM_CODE:
		return joinRoom(request);
    }
}

RequestResult MenuRequestHandler::signout(const RequestInfo& ri)
{
	this->m_handlerFactory.getLoginManager().logout(m_user.getUsername());
	RequestResult result;
	LogoutResponse logResp;
	logResp.status = STATUS_OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(logResp);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& ri)
{
	RequestResult result;
	GetRoomsResponse getRoomsResp;
	vector<Room> allRooms = this->m_handlerFactory.getRoomManager().getRooms();

	for (const auto& room : allRooms)
	{
		getRoomsResp.rooms.push_back(room.getRoomData());
	}
	getRoomsResp.status = STATUS_OK;

	// Serialize the response
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResp);
	result.newHandler = this;
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& ri)
{
	RequestResult result;
	GetPlayersInRoomResponse getPlayersResp;
	GetPlayersInRoomRequest getPlayersReq = JsonResponsePacketDeserializer::deserializeGetPlayersInRoomRequest(ri.buffer);

	Room room = this->m_handlerFactory.getRoomManager().getRoom(getPlayersReq.roomId);

	getPlayersResp.players = room.getAllUsers();
	
	result.response = JsonResponsePacketSerializer::serializeResponse(getPlayersResp);
	result.newHandler = this;

	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& ri)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& ri)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& ri)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& ri)
{
    return RequestResult();
}

